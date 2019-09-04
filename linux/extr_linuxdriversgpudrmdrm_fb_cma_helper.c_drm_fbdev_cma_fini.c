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
 int /*<<< orphan*/  drm_fb_helper_unregister_fbi (int /*<<< orphan*/ *) ; 

void drm_fbdev_cma_fini(struct drm_fbdev_cma *fbdev_cma)
{
	drm_fb_helper_unregister_fbi(&fbdev_cma->fb_helper);
	/* All resources have now been freed by drm_fbdev_fb_destroy() */
}