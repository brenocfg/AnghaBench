#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct omapfb_info {int num_overlays; TYPE_2__* region; TYPE_1__** overlays; int /*<<< orphan*/  id; } ;
struct omap_video_timings {int pixelclock; scalar_t__ hsync_level; scalar_t__ vsync_level; scalar_t__ interlace; scalar_t__ vsw; scalar_t__ hsw; scalar_t__ vfp; scalar_t__ vbp; scalar_t__ hfp; scalar_t__ hbp; } ;
struct omap_dss_device {TYPE_3__* driver; } ;
struct fb_var_screeninfo {int rotate; scalar_t__ xres; scalar_t__ xoffset; scalar_t__ xres_virtual; scalar_t__ yres; scalar_t__ yoffset; scalar_t__ yres_virtual; int width; int height; void* vmode; int /*<<< orphan*/  sync; scalar_t__ vsync_len; scalar_t__ hsync_len; scalar_t__ lower_margin; scalar_t__ upper_margin; scalar_t__ right_margin; scalar_t__ left_margin; scalar_t__ pixclock; scalar_t__ grayscale; } ;
struct fb_info {int dummy; } ;
typedef  enum omap_color_mode { ____Placeholder_omap_color_mode } omap_color_mode ;
struct TYPE_6__ {int /*<<< orphan*/  (* get_timings ) (struct omap_dss_device*,struct omap_video_timings*) ;int /*<<< orphan*/  (* get_dimensions ) (struct omap_dss_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {scalar_t__ size; int /*<<< orphan*/  lock_count; } ;
struct TYPE_4__ {int supported_modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 void* DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 struct omapfb_info* FB2OFB (struct fb_info*) ; 
 int /*<<< orphan*/  FB_SYNC_HOR_HIGH_ACT ; 
 int /*<<< orphan*/  FB_SYNC_VERT_HIGH_ACT ; 
 void* FB_VMODE_INTERLACED ; 
 void* FB_VMODE_NONINTERLACED ; 
 scalar_t__ KHZ2PICOS (int) ; 
 scalar_t__ OMAPDSS_SIG_ACTIVE_HIGH ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ check_fb_res_bounds (struct fb_var_screeninfo*) ; 
 scalar_t__ check_fb_size (struct omapfb_info*,struct fb_var_screeninfo*) ; 
 struct omap_dss_device* fb2display (struct fb_info*) ; 
 int fb_mode_to_dss_mode (struct fb_var_screeninfo*,int*) ; 
 int /*<<< orphan*/  stub1 (struct omap_dss_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct omap_dss_device*,struct omap_video_timings*) ; 

int check_fb_var(struct fb_info *fbi, struct fb_var_screeninfo *var)
{
	struct omapfb_info *ofbi = FB2OFB(fbi);
	struct omap_dss_device *display = fb2display(fbi);
	enum omap_color_mode mode = 0;
	int i;
	int r;

	DBG("check_fb_var %d\n", ofbi->id);

	WARN_ON(!atomic_read(&ofbi->region->lock_count));

	r = fb_mode_to_dss_mode(var, &mode);
	if (r) {
		DBG("cannot convert var to omap dss mode\n");
		return r;
	}

	for (i = 0; i < ofbi->num_overlays; ++i) {
		if ((ofbi->overlays[i]->supported_modes & mode) == 0) {
			DBG("invalid mode\n");
			return -EINVAL;
		}
	}

	if (var->rotate > 3)
		return -EINVAL;

	if (check_fb_res_bounds(var))
		return -EINVAL;

	/* When no memory is allocated ignore the size check */
	if (ofbi->region->size != 0 && check_fb_size(ofbi, var))
		return -EINVAL;

	if (var->xres + var->xoffset > var->xres_virtual)
		var->xoffset = var->xres_virtual - var->xres;
	if (var->yres + var->yoffset > var->yres_virtual)
		var->yoffset = var->yres_virtual - var->yres;

	DBG("xres = %d, yres = %d, vxres = %d, vyres = %d\n",
			var->xres, var->yres,
			var->xres_virtual, var->yres_virtual);

	if (display && display->driver->get_dimensions) {
		u32 w, h;
		display->driver->get_dimensions(display, &w, &h);
		var->width = DIV_ROUND_CLOSEST(w, 1000);
		var->height = DIV_ROUND_CLOSEST(h, 1000);
	} else {
		var->height = -1;
		var->width = -1;
	}

	var->grayscale          = 0;

	if (display && display->driver->get_timings) {
		struct omap_video_timings timings;
		display->driver->get_timings(display, &timings);

		/* pixclock in ps, the rest in pixclock */
		var->pixclock = timings.pixelclock != 0 ?
			KHZ2PICOS(timings.pixelclock / 1000) :
			0;
		var->left_margin = timings.hbp;
		var->right_margin = timings.hfp;
		var->upper_margin = timings.vbp;
		var->lower_margin = timings.vfp;
		var->hsync_len = timings.hsw;
		var->vsync_len = timings.vsw;
		var->sync |= timings.hsync_level == OMAPDSS_SIG_ACTIVE_HIGH ?
				FB_SYNC_HOR_HIGH_ACT : 0;
		var->sync |= timings.vsync_level == OMAPDSS_SIG_ACTIVE_HIGH ?
				FB_SYNC_VERT_HIGH_ACT : 0;
		var->vmode = timings.interlace ?
				FB_VMODE_INTERLACED : FB_VMODE_NONINTERLACED;
	} else {
		var->pixclock = 0;
		var->left_margin = 0;
		var->right_margin = 0;
		var->upper_margin = 0;
		var->lower_margin = 0;
		var->hsync_len = 0;
		var->vsync_len = 0;
		var->sync = 0;
		var->vmode = FB_VMODE_NONINTERLACED;
	}

	return 0;
}