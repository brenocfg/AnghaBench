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
struct mmp_mode {scalar_t__ invert_pixclock; scalar_t__ vsync_invert; scalar_t__ hsync_invert; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  lower_margin; int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  right_margin; int /*<<< orphan*/  left_margin; int /*<<< orphan*/  pixclock_freq; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; int /*<<< orphan*/  refresh; int /*<<< orphan*/  name; } ;
struct fb_videomode {int sync; int vmode; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  lower_margin; int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  right_margin; int /*<<< orphan*/  left_margin; scalar_t__ pixclock; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; int /*<<< orphan*/  refresh; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 int /*<<< orphan*/  do_div (long long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mmpmode_to_fbmode(struct fb_videomode *videomode,
		struct mmp_mode *mode)
{
	u64 div_result = 1000000000000ll;

	videomode->name = mode->name;
	videomode->refresh = mode->refresh;
	videomode->xres = mode->xres;
	videomode->yres = mode->yres;

	do_div(div_result, mode->pixclock_freq);
	videomode->pixclock = (u32)div_result;

	videomode->left_margin = mode->left_margin;
	videomode->right_margin = mode->right_margin;
	videomode->upper_margin = mode->upper_margin;
	videomode->lower_margin = mode->lower_margin;
	videomode->hsync_len = mode->hsync_len;
	videomode->vsync_len = mode->vsync_len;
	videomode->sync = (mode->hsync_invert ? FB_SYNC_HOR_HIGH_ACT : 0)
		| (mode->vsync_invert ? FB_SYNC_VERT_HIGH_ACT : 0);
	videomode->vmode = mode->invert_pixclock ? 8 : 0;
}