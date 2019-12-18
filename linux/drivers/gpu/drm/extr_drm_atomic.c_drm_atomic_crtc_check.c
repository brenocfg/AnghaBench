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
struct drm_crtc_state {scalar_t__ active; scalar_t__ event; scalar_t__ mode_blob; scalar_t__ enable; struct drm_crtc* crtc; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_crtc {int /*<<< orphan*/  name; TYPE_1__ base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_ATOMIC ; 
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ drm_core_check_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drm_atomic_crtc_check(const struct drm_crtc_state *old_crtc_state,
				 const struct drm_crtc_state *new_crtc_state)
{
	struct drm_crtc *crtc = new_crtc_state->crtc;

	/* NOTE: we explicitly don't enforce constraints such as primary
	 * layer covering entire screen, since that is something we want
	 * to allow (on hw that supports it).  For hw that does not, it
	 * should be checked in driver's crtc->atomic_check() vfunc.
	 *
	 * TODO: Add generic modeset state checks once we support those.
	 */

	if (new_crtc_state->active && !new_crtc_state->enable) {
		DRM_DEBUG_ATOMIC("[CRTC:%d:%s] active without enabled\n",
				 crtc->base.id, crtc->name);
		return -EINVAL;
	}

	/* The state->enable vs. state->mode_blob checks can be WARN_ON,
	 * as this is a kernel-internal detail that userspace should never
	 * be able to trigger. */
	if (drm_core_check_feature(crtc->dev, DRIVER_ATOMIC) &&
	    WARN_ON(new_crtc_state->enable && !new_crtc_state->mode_blob)) {
		DRM_DEBUG_ATOMIC("[CRTC:%d:%s] enabled without mode blob\n",
				 crtc->base.id, crtc->name);
		return -EINVAL;
	}

	if (drm_core_check_feature(crtc->dev, DRIVER_ATOMIC) &&
	    WARN_ON(!new_crtc_state->enable && new_crtc_state->mode_blob)) {
		DRM_DEBUG_ATOMIC("[CRTC:%d:%s] disabled with mode blob\n",
				 crtc->base.id, crtc->name);
		return -EINVAL;
	}

	/*
	 * Reject event generation for when a CRTC is off and stays off.
	 * It wouldn't be hard to implement this, but userspace has a track
	 * record of happily burning through 100% cpu (or worse, crash) when the
	 * display pipe is suspended. To avoid all that fun just reject updates
	 * that ask for events since likely that indicates a bug in the
	 * compositor's drawing loop. This is consistent with the vblank IOCTL
	 * and legacy page_flip IOCTL which also reject service on a disabled
	 * pipe.
	 */
	if (new_crtc_state->event &&
	    !new_crtc_state->active && !old_crtc_state->active) {
		DRM_DEBUG_ATOMIC("[CRTC:%d:%s] requesting event but off\n",
				 crtc->base.id, crtc->name);
		return -EINVAL;
	}

	return 0;
}