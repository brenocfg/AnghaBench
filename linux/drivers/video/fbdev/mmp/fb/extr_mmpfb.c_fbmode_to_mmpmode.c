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
typedef  long long u64 ;
typedef  scalar_t__ u32 ;
struct mmp_mode {int hsync_invert; int vsync_invert; int invert_pixclock; int pix_fmt_out; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  lower_margin; int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  right_margin; int /*<<< orphan*/  left_margin; scalar_t__ pixclock_freq; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; int /*<<< orphan*/  refresh; int /*<<< orphan*/  name; } ;
struct fb_videomode {int sync; int vmode; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  lower_margin; int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  right_margin; int /*<<< orphan*/  left_margin; int /*<<< orphan*/  pixclock; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; int /*<<< orphan*/  refresh; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 int /*<<< orphan*/  do_div (long long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fbmode_to_mmpmode(struct mmp_mode *mode,
		struct fb_videomode *videomode, int output_fmt)
{
	u64 div_result = 1000000000000ll;
	mode->name = videomode->name;
	mode->refresh = videomode->refresh;
	mode->xres = videomode->xres;
	mode->yres = videomode->yres;

	do_div(div_result, videomode->pixclock);
	mode->pixclock_freq = (u32)div_result;

	mode->left_margin = videomode->left_margin;
	mode->right_margin = videomode->right_margin;
	mode->upper_margin = videomode->upper_margin;
	mode->lower_margin = videomode->lower_margin;
	mode->hsync_len = videomode->hsync_len;
	mode->vsync_len = videomode->vsync_len;
	mode->hsync_invert = !!(videomode->sync & FB_SYNC_HOR_HIGH_ACT);
	mode->vsync_invert = !!(videomode->sync & FB_SYNC_VERT_HIGH_ACT);
	/* no defined flag in fb, use vmode>>3*/
	mode->invert_pixclock = !!(videomode->vmode & 8);
	mode->pix_fmt_out = output_fmt;
}