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
struct drm_device {struct arcpgu_drm_private* dev_private; } ;
struct arcpgu_drm_private {int /*<<< orphan*/ * fbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fbdev_cma_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 

__attribute__((used)) static int arcpgu_unload(struct drm_device *drm)
{
	struct arcpgu_drm_private *arcpgu = drm->dev_private;

	if (arcpgu->fbdev) {
		drm_fbdev_cma_fini(arcpgu->fbdev);
		arcpgu->fbdev = NULL;
	}
	drm_kms_helper_poll_fini(drm);
	drm_mode_config_cleanup(drm);

	return 0;
}