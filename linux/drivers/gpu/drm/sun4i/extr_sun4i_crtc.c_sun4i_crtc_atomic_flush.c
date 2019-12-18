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
struct sun4i_crtc {int /*<<< orphan*/  engine; } ;
struct drm_pending_vblank_event {int dummy; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_1__* dev; TYPE_2__* state; } ;
struct TYPE_4__ {struct drm_pending_vblank_event* event; } ;
struct TYPE_3__ {int /*<<< orphan*/  event_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  drm_crtc_arm_vblank_event (struct drm_crtc*,struct drm_pending_vblank_event*) ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,struct drm_pending_vblank_event*) ; 
 struct sun4i_crtc* drm_crtc_to_sun4i_crtc (struct drm_crtc*) ; 
 scalar_t__ drm_crtc_vblank_get (struct drm_crtc*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunxi_engine_commit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun4i_crtc_atomic_flush(struct drm_crtc *crtc,
				    struct drm_crtc_state *old_state)
{
	struct sun4i_crtc *scrtc = drm_crtc_to_sun4i_crtc(crtc);
	struct drm_pending_vblank_event *event = crtc->state->event;

	DRM_DEBUG_DRIVER("Committing plane changes\n");

	sunxi_engine_commit(scrtc->engine);

	if (event) {
		crtc->state->event = NULL;

		spin_lock_irq(&crtc->dev->event_lock);
		if (drm_crtc_vblank_get(crtc) == 0)
			drm_crtc_arm_vblank_event(crtc, event);
		else
			drm_crtc_send_vblank_event(crtc, event);
		spin_unlock_irq(&crtc->dev->event_lock);
	}
}