#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct videomode {int flags; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  vfront_porch; int /*<<< orphan*/  vback_porch; int /*<<< orphan*/  vactive; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  hfront_porch; int /*<<< orphan*/  hback_porch; int /*<<< orphan*/  hactive; int /*<<< orphan*/  pixelclock; } ;
struct omap_video_timings {int /*<<< orphan*/  data_pclk_edge; int /*<<< orphan*/  sync_pclk_edge; void* de_level; void* hsync_level; void* vsync_level; int /*<<< orphan*/  vsw; int /*<<< orphan*/  vfp; int /*<<< orphan*/  vbp; int /*<<< orphan*/  y_res; int /*<<< orphan*/  hsw; int /*<<< orphan*/  hfp; int /*<<< orphan*/  hbp; int /*<<< orphan*/  x_res; int /*<<< orphan*/  pixelclock; } ;

/* Variables and functions */
 int DISPLAY_FLAGS_DE_HIGH ; 
 int DISPLAY_FLAGS_HSYNC_HIGH ; 
 int DISPLAY_FLAGS_PIXDATA_POSEDGE ; 
 int DISPLAY_FLAGS_VSYNC_HIGH ; 
 int /*<<< orphan*/  OMAPDSS_DRIVE_SIG_FALLING_EDGE ; 
 int /*<<< orphan*/  OMAPDSS_DRIVE_SIG_RISING_EDGE ; 
 void* OMAPDSS_SIG_ACTIVE_HIGH ; 
 void* OMAPDSS_SIG_ACTIVE_LOW ; 
 int /*<<< orphan*/  memset (struct omap_video_timings*,int /*<<< orphan*/ ,int) ; 

void videomode_to_omap_video_timings(const struct videomode *vm,
		struct omap_video_timings *ovt)
{
	memset(ovt, 0, sizeof(*ovt));

	ovt->pixelclock = vm->pixelclock;
	ovt->x_res = vm->hactive;
	ovt->hbp = vm->hback_porch;
	ovt->hfp = vm->hfront_porch;
	ovt->hsw = vm->hsync_len;
	ovt->y_res = vm->vactive;
	ovt->vbp = vm->vback_porch;
	ovt->vfp = vm->vfront_porch;
	ovt->vsw = vm->vsync_len;

	ovt->vsync_level = vm->flags & DISPLAY_FLAGS_VSYNC_HIGH ?
		OMAPDSS_SIG_ACTIVE_HIGH :
		OMAPDSS_SIG_ACTIVE_LOW;
	ovt->hsync_level = vm->flags & DISPLAY_FLAGS_HSYNC_HIGH ?
		OMAPDSS_SIG_ACTIVE_HIGH :
		OMAPDSS_SIG_ACTIVE_LOW;
	ovt->de_level = vm->flags & DISPLAY_FLAGS_DE_HIGH ?
		OMAPDSS_SIG_ACTIVE_HIGH :
		OMAPDSS_SIG_ACTIVE_LOW;
	ovt->data_pclk_edge = vm->flags & DISPLAY_FLAGS_PIXDATA_POSEDGE ?
		OMAPDSS_DRIVE_SIG_RISING_EDGE :
		OMAPDSS_DRIVE_SIG_FALLING_EDGE;

	ovt->sync_pclk_edge = ovt->data_pclk_edge;
}