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

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __drm_helper_disable_unused_functions (struct drm_device*) ; 
 int /*<<< orphan*/  drm_drv_uses_atomic_modeset (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_lock_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (struct drm_device*) ; 

void drm_helper_disable_unused_functions(struct drm_device *dev)
{
	WARN_ON(drm_drv_uses_atomic_modeset(dev));

	drm_modeset_lock_all(dev);
	__drm_helper_disable_unused_functions(dev);
	drm_modeset_unlock_all(dev);
}