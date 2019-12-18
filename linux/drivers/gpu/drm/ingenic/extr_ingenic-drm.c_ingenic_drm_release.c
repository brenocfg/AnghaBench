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
struct ingenic_drm {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dev_fini (struct drm_device*) ; 
 struct ingenic_drm* drm_device_get_priv (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  kfree (struct ingenic_drm*) ; 

__attribute__((used)) static void ingenic_drm_release(struct drm_device *drm)
{
	struct ingenic_drm *priv = drm_device_get_priv(drm);

	drm_mode_config_cleanup(drm);
	drm_dev_fini(drm);
	kfree(priv);
}