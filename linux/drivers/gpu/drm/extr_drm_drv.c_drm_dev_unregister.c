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
struct drm_device {int registered; scalar_t__ agp; TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unload ) (struct drm_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_LEGACY ; 
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  DRM_MINOR_PRIMARY ; 
 int /*<<< orphan*/  DRM_MINOR_RENDER ; 
 int /*<<< orphan*/  drm_client_dev_unregister (struct drm_device*) ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_lastclose (struct drm_device*) ; 
 int /*<<< orphan*/  drm_legacy_rmmaps (struct drm_device*) ; 
 int /*<<< orphan*/  drm_minor_unregister (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_unregister_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_pci_agp_destroy (struct drm_device*) ; 
 int /*<<< orphan*/  remove_compat_control_link (struct drm_device*) ; 
 int /*<<< orphan*/  stub1 (struct drm_device*) ; 

void drm_dev_unregister(struct drm_device *dev)
{
	if (drm_core_check_feature(dev, DRIVER_LEGACY))
		drm_lastclose(dev);

	dev->registered = false;

	drm_client_dev_unregister(dev);

	if (drm_core_check_feature(dev, DRIVER_MODESET))
		drm_modeset_unregister_all(dev);

	if (dev->driver->unload)
		dev->driver->unload(dev);

	if (dev->agp)
		drm_pci_agp_destroy(dev);

	drm_legacy_rmmaps(dev);

	remove_compat_control_link(dev);
	drm_minor_unregister(dev, DRM_MINOR_PRIMARY);
	drm_minor_unregister(dev, DRM_MINOR_RENDER);
}