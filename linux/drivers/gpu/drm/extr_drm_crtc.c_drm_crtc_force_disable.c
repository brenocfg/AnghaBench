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
struct drm_mode_set {struct drm_crtc* crtc; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_drv_uses_atomic_modeset (int /*<<< orphan*/ ) ; 
 int drm_mode_set_config_internal (struct drm_mode_set*) ; 

int drm_crtc_force_disable(struct drm_crtc *crtc)
{
	struct drm_mode_set set = {
		.crtc = crtc,
	};

	WARN_ON(drm_drv_uses_atomic_modeset(crtc->dev));

	return drm_mode_set_config_internal(&set);
}