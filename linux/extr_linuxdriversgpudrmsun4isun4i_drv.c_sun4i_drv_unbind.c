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
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int /*<<< orphan*/  drm_dev_unregister (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  of_reserved_mem_device_release (struct device*) ; 
 int /*<<< orphan*/  sun4i_framebuffer_free (struct drm_device*) ; 

__attribute__((used)) static void sun4i_drv_unbind(struct device *dev)
{
	struct drm_device *drm = dev_get_drvdata(dev);

	drm_dev_unregister(drm);
	drm_kms_helper_poll_fini(drm);
	sun4i_framebuffer_free(drm);
	drm_mode_config_cleanup(drm);
	of_reserved_mem_device_release(dev);
	drm_dev_put(drm);
}