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
struct drm_fb_helper {scalar_t__ fbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  fb_set_suspend (scalar_t__,int) ; 

void drm_fb_helper_set_suspend(struct drm_fb_helper *fb_helper, bool suspend)
{
	if (fb_helper && fb_helper->fbdev)
		fb_set_suspend(fb_helper->fbdev, suspend);
}