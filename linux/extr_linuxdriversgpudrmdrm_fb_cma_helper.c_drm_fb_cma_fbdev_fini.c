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
struct drm_device {scalar_t__ fb_helper; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fbdev_cma_fini (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_fbdev_cma (scalar_t__) ; 

void drm_fb_cma_fbdev_fini(struct drm_device *dev)
{
	if (dev->fb_helper)
		drm_fbdev_cma_fini(to_fbdev_cma(dev->fb_helper));
}