#include <Elementary.h>
#include <Ecore_Wayland.h>

static void
_scale_set(void)
{
   Evas_Coord w, h, tw, th;
   float inch, scale = 0.0, profile_factor = 1.0;
   int dpi;
   char *s = NULL;

   ecore_wl_sync();
   dpi = ecore_wl_dpi_get();
   ecore_wl_screen_size_get(&w, &h);

   inch = floor(sqrt((w * w) + (h * h)) / dpi * 10 + 0.5) / 10;

   if (inch <= 4.5) profile_factor = 0.7;
   else profile_factor = 0.8;

   scale = floor((double)dpi * profile_factor / 90.0 * 10 + 0.5) / 10;

   s = getenv("ELM_SCALE");
   if (!s) elm_config_scale_set(scale);

   elm_config_save();
   elm_config_all_flush();
}

int main(int argc, char **argv)
{
   Evas_Object *win;

   elm_init(argc, argv);

   win = elm_win_add(NULL, "config", ELM_WIN_BASIC);

   _scale_set();

   //  This program will end after setting the scale value.
   //  If it should stay alive, remove this comment.
   //  elm_run();

   elm_shutdown();

   return 0;
}
