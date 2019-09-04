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
struct drm_fbdev_cma {int /*<<< orphan*/  fb_helper; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_set_suspend_unlocked (int /*<<< orphan*/ *,int) ; 

void drm_fbdev_cma_set_suspend_unlocked(struct drm_fbdev_cma *fbdev_cma,
					bool state)
{
	if (fbdev_cma)
		drm_fb_helper_set_suspend_unlocked(&fbdev_cma->fb_helper,
						   state);
}