#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct omap_video_timings {int pixelclock; int interlace; void* vsync_level; void* hsync_level; int /*<<< orphan*/  y_res; int /*<<< orphan*/  x_res; int /*<<< orphan*/  vsw; int /*<<< orphan*/  hsw; int /*<<< orphan*/  vfp; int /*<<< orphan*/  vbp; int /*<<< orphan*/  hfp; int /*<<< orphan*/  hbp; int /*<<< orphan*/  sync_pclk_edge; void* de_level; int /*<<< orphan*/  data_pclk_edge; } ;
struct omap_dss_device {TYPE_1__* driver; } ;
struct fb_var_screeninfo {int sync; int vmode; int bits_per_pixel; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  lower_margin; int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  right_margin; int /*<<< orphan*/  left_margin; int /*<<< orphan*/  pixclock; struct fb_var_screeninfo* fbops; } ;
struct fb_ops {int sync; int vmode; int bits_per_pixel; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  lower_margin; int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  right_margin; int /*<<< orphan*/  left_margin; int /*<<< orphan*/  pixclock; struct fb_ops* fbops; } ;
struct fb_info {int sync; int vmode; int bits_per_pixel; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  lower_margin; int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  right_margin; int /*<<< orphan*/  left_margin; int /*<<< orphan*/  pixclock; struct fb_info* fbops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_timings ) (struct omap_dss_device*,struct omap_video_timings*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 int FB_VMODE_INTERLACED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OMAPDSS_DRIVE_SIG_FALLING_EDGE ; 
 int /*<<< orphan*/  OMAPDSS_DRIVE_SIG_RISING_EDGE ; 
 void* OMAPDSS_SIG_ACTIVE_HIGH ; 
 void* OMAPDSS_SIG_ACTIVE_LOW ; 
 int PICOS2KHZ (int /*<<< orphan*/ ) ; 
 int fb_find_mode (struct fb_var_screeninfo*,struct fb_var_screeninfo*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct fb_var_screeninfo*) ; 
 struct fb_var_screeninfo* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct omap_video_timings omap_dss_ntsc_timings ; 
 struct omap_video_timings omap_dss_pal_timings ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  stub1 (struct omap_dss_device*,struct omap_video_timings*) ; 

__attribute__((used)) static int omapfb_mode_to_timings(const char *mode_str,
		struct omap_dss_device *display,
		struct omap_video_timings *timings, u8 *bpp)
{
	struct fb_info *fbi;
	struct fb_var_screeninfo *var;
	struct fb_ops *fbops;
	int r;

#ifdef CONFIG_OMAP2_DSS_VENC
	if (strcmp(mode_str, "pal") == 0) {
		*timings = omap_dss_pal_timings;
		*bpp = 24;
		return 0;
	} else if (strcmp(mode_str, "ntsc") == 0) {
		*timings = omap_dss_ntsc_timings;
		*bpp = 24;
		return 0;
	}
#endif

	/* this is quite a hack, but I wanted to use the modedb and for
	 * that we need fb_info and var, so we create dummy ones */

	*bpp = 0;
	fbi = NULL;
	var = NULL;
	fbops = NULL;

	fbi = kzalloc(sizeof(*fbi), GFP_KERNEL);
	if (fbi == NULL) {
		r = -ENOMEM;
		goto err;
	}

	var = kzalloc(sizeof(*var), GFP_KERNEL);
	if (var == NULL) {
		r = -ENOMEM;
		goto err;
	}

	fbops = kzalloc(sizeof(*fbops), GFP_KERNEL);
	if (fbops == NULL) {
		r = -ENOMEM;
		goto err;
	}

	fbi->fbops = fbops;

	r = fb_find_mode(var, fbi, mode_str, NULL, 0, NULL, 24);
	if (r == 0) {
		r = -EINVAL;
		goto err;
	}

	if (display->driver->get_timings) {
		display->driver->get_timings(display, timings);
	} else {
		timings->data_pclk_edge = OMAPDSS_DRIVE_SIG_RISING_EDGE;
		timings->de_level = OMAPDSS_SIG_ACTIVE_HIGH;
		timings->sync_pclk_edge = OMAPDSS_DRIVE_SIG_FALLING_EDGE;
	}

	timings->pixelclock = PICOS2KHZ(var->pixclock) * 1000;
	timings->hbp = var->left_margin;
	timings->hfp = var->right_margin;
	timings->vbp = var->upper_margin;
	timings->vfp = var->lower_margin;
	timings->hsw = var->hsync_len;
	timings->vsw = var->vsync_len;
	timings->x_res = var->xres;
	timings->y_res = var->yres;
	timings->hsync_level = var->sync & FB_SYNC_HOR_HIGH_ACT ?
				OMAPDSS_SIG_ACTIVE_HIGH :
				OMAPDSS_SIG_ACTIVE_LOW;
	timings->vsync_level = var->sync & FB_SYNC_VERT_HIGH_ACT ?
				OMAPDSS_SIG_ACTIVE_HIGH :
				OMAPDSS_SIG_ACTIVE_LOW;
	timings->interlace = var->vmode & FB_VMODE_INTERLACED;

	switch (var->bits_per_pixel) {
	case 16:
		*bpp = 16;
		break;
	case 24:
	case 32:
	default:
		*bpp = 24;
		break;
	}

	r = 0;

err:
	kfree(fbi);
	kfree(var);
	kfree(fbops);

	return r;
}