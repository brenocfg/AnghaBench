#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct drm_pending_vblank_event {int dummy; } ;
struct TYPE_7__ {int flags; } ;
struct drm_crtc_state {TYPE_2__ adjusted_mode; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct drm_crtc {TYPE_5__* dev; TYPE_4__* state; int /*<<< orphan*/  name; TYPE_1__ base; } ;
struct armada_crtc {TYPE_3__* variant; } ;
struct TYPE_10__ {int /*<<< orphan*/  event_lock; } ;
struct TYPE_9__ {struct drm_pending_vblank_event* event; int /*<<< orphan*/  active; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* disable ) (struct armada_crtc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int /*<<< orphan*/  armada_drm_crtc_update (struct armada_crtc*,int) ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,struct drm_pending_vblank_event*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_put (struct drm_crtc*) ; 
 struct armada_crtc* drm_to_armada_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct armada_crtc*) ; 

__attribute__((used)) static void armada_drm_crtc_atomic_disable(struct drm_crtc *crtc,
					   struct drm_crtc_state *old_state)
{
	struct armada_crtc *dcrtc = drm_to_armada_crtc(crtc);
	struct drm_pending_vblank_event *event;

	DRM_DEBUG_KMS("[CRTC:%d:%s]\n", crtc->base.id, crtc->name);

	if (old_state->adjusted_mode.flags & DRM_MODE_FLAG_INTERLACE)
		drm_crtc_vblank_put(crtc);

	drm_crtc_vblank_off(crtc);
	armada_drm_crtc_update(dcrtc, false);

	if (!crtc->state->active) {
		/*
		 * This modeset will be leaving the CRTC disabled, so
		 * call the backend to disable upstream clocks etc.
		 */
		if (dcrtc->variant->disable)
			dcrtc->variant->disable(dcrtc);

		/*
		 * We will not receive any further vblank events.
		 * Send the flip_done event manually.
		 */
		event = crtc->state->event;
		crtc->state->event = NULL;
		if (event) {
			spin_lock_irq(&crtc->dev->event_lock);
			drm_crtc_send_vblank_event(crtc, event);
			spin_unlock_irq(&crtc->dev->event_lock);
		}
	}
}