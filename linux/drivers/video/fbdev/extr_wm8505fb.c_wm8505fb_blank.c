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
struct wm8505fb_info {scalar_t__ regbase; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
#define  FB_BLANK_UNBLANK 128 
 scalar_t__ WMT_GOVR_TIMING_V_SYNC ; 
 struct wm8505fb_info* to_wm8505fb_info (struct fb_info*) ; 
 int /*<<< orphan*/  wm8505fb_set_timing (struct fb_info*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int wm8505fb_blank(int blank, struct fb_info *info)
{
	struct wm8505fb_info *fbi = to_wm8505fb_info(info);

	switch (blank) {
	case FB_BLANK_UNBLANK:
		wm8505fb_set_timing(info);
		break;
	default:
		writel(0,  fbi->regbase + WMT_GOVR_TIMING_V_SYNC);
		break;
	}

	return 0;
}