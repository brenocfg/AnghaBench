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
struct repaper_epd {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  drm_dev_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 struct repaper_epd* drm_to_epd (struct drm_device*) ; 
 int /*<<< orphan*/  kfree (struct repaper_epd*) ; 

__attribute__((used)) static void repaper_release(struct drm_device *drm)
{
	struct repaper_epd *epd = drm_to_epd(drm);

	DRM_DEBUG_DRIVER("\n");

	drm_mode_config_cleanup(drm);
	drm_dev_fini(drm);
	kfree(epd);
}