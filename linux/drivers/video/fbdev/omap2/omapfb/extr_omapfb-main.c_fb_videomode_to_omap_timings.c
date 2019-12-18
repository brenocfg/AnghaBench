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
struct omap_video_timings {int pixelclock; int interlace; void* vsync_level; void* hsync_level; int /*<<< orphan*/  vbp; int /*<<< orphan*/  vfp; int /*<<< orphan*/  vsw; int /*<<< orphan*/  hbp; int /*<<< orphan*/  hfp; int /*<<< orphan*/  hsw; int /*<<< orphan*/  y_res; int /*<<< orphan*/  x_res; int /*<<< orphan*/  sync_pclk_edge; void* de_level; int /*<<< orphan*/  data_pclk_edge; } ;
struct omap_dss_device {TYPE_1__* driver; } ;
struct fb_videomode {int sync; int vmode; int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  lower_margin; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  left_margin; int /*<<< orphan*/  right_margin; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  pixclock; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_timings ) (struct omap_dss_device*,struct omap_video_timings*) ;} ;

/* Variables and functions */
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 int FB_VMODE_INTERLACED ; 
 int /*<<< orphan*/  OMAPDSS_DRIVE_SIG_FALLING_EDGE ; 
 int /*<<< orphan*/  OMAPDSS_DRIVE_SIG_RISING_EDGE ; 
 void* OMAPDSS_SIG_ACTIVE_HIGH ; 
 void* OMAPDSS_SIG_ACTIVE_LOW ; 
 int PICOS2KHZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct omap_dss_device*,struct omap_video_timings*) ; 

__attribute__((used)) static void fb_videomode_to_omap_timings(struct fb_videomode *m,
		struct omap_dss_device *display,
		struct omap_video_timings *t)
{
	if (display->driver->get_timings) {
		display->driver->get_timings(display, t);
	} else {
		t->data_pclk_edge = OMAPDSS_DRIVE_SIG_RISING_EDGE;
		t->de_level = OMAPDSS_SIG_ACTIVE_HIGH;
		t->sync_pclk_edge = OMAPDSS_DRIVE_SIG_FALLING_EDGE;
	}

	t->x_res = m->xres;
	t->y_res = m->yres;
	t->pixelclock = PICOS2KHZ(m->pixclock) * 1000;
	t->hsw = m->hsync_len;
	t->hfp = m->right_margin;
	t->hbp = m->left_margin;
	t->vsw = m->vsync_len;
	t->vfp = m->lower_margin;
	t->vbp = m->upper_margin;
	t->hsync_level = m->sync & FB_SYNC_HOR_HIGH_ACT ?
				OMAPDSS_SIG_ACTIVE_HIGH :
				OMAPDSS_SIG_ACTIVE_LOW;
	t->vsync_level = m->sync & FB_SYNC_VERT_HIGH_ACT ?
				OMAPDSS_SIG_ACTIVE_HIGH :
				OMAPDSS_SIG_ACTIVE_LOW;
	t->interlace = m->vmode & FB_VMODE_INTERLACED;
}