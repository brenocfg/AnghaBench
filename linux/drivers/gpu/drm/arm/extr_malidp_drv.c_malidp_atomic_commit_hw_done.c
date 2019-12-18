#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* state; } ;
struct malidp_drm {int /*<<< orphan*/ * event; TYPE_2__ crtc; } ;
struct drm_device {int /*<<< orphan*/  event_lock; struct malidp_drm* dev_private; } ;
struct drm_atomic_state {struct drm_device* dev; } ;
struct TYPE_4__ {scalar_t__ active; int /*<<< orphan*/ * event; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  drm_atomic_helper_commit_hw_done (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_vblank_get (TYPE_2__*) ; 
 scalar_t__ malidp_set_and_wait_config_valid (struct drm_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void malidp_atomic_commit_hw_done(struct drm_atomic_state *state)
{
	struct drm_device *drm = state->dev;
	struct malidp_drm *malidp = drm->dev_private;
	int loop = 5;

	malidp->event = malidp->crtc.state->event;
	malidp->crtc.state->event = NULL;

	if (malidp->crtc.state->active) {
		/*
		 * if we have an event to deliver to userspace, make sure
		 * the vblank is enabled as we are sending it from the IRQ
		 * handler.
		 */
		if (malidp->event)
			drm_crtc_vblank_get(&malidp->crtc);

		/* only set config_valid if the CRTC is enabled */
		if (malidp_set_and_wait_config_valid(drm) < 0) {
			/*
			 * make a loop around the second CVAL setting and
			 * try 5 times before giving up.
			 */
			while (loop--) {
				if (!malidp_set_and_wait_config_valid(drm))
					break;
			}
			DRM_DEBUG_DRIVER("timed out waiting for updated configuration\n");
		}

	} else if (malidp->event) {
		/* CRTC inactive means vblank IRQ is disabled, send event directly */
		spin_lock_irq(&drm->event_lock);
		drm_crtc_send_vblank_event(&malidp->crtc, malidp->event);
		malidp->event = NULL;
		spin_unlock_irq(&drm->event_lock);
	}
	drm_atomic_helper_commit_hw_done(state);
}