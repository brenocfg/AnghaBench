#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_device {TYPE_2__* driver; } ;
struct drm_crtc {TYPE_1__* funcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* disable_vblank ) (struct drm_device*,unsigned int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* disable_vblank ) (struct drm_crtc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 struct drm_crtc* drm_crtc_from_index (struct drm_device*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct drm_crtc*) ; 
 int /*<<< orphan*/  stub2 (struct drm_device*,unsigned int) ; 

__attribute__((used)) static void __disable_vblank(struct drm_device *dev, unsigned int pipe)
{
	if (drm_core_check_feature(dev, DRIVER_MODESET)) {
		struct drm_crtc *crtc = drm_crtc_from_index(dev, pipe);

		if (WARN_ON(!crtc))
			return;

		if (crtc->funcs->disable_vblank) {
			crtc->funcs->disable_vblank(crtc);
			return;
		}
	}

	dev->driver->disable_vblank(dev, pipe);
}