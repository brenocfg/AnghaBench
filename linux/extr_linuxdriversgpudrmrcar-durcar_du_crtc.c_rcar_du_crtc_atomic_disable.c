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
struct rcar_du_crtc {int initialized; scalar_t__ outputs; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_1__* dev; TYPE_2__* state; } ;
struct TYPE_4__ {int /*<<< orphan*/ * event; } ;
struct TYPE_3__ {int /*<<< orphan*/  event_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcar_du_crtc_put (struct rcar_du_crtc*) ; 
 int /*<<< orphan*/  rcar_du_crtc_stop (struct rcar_du_crtc*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct rcar_du_crtc* to_rcar_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void rcar_du_crtc_atomic_disable(struct drm_crtc *crtc,
					struct drm_crtc_state *old_state)
{
	struct rcar_du_crtc *rcrtc = to_rcar_crtc(crtc);

	rcar_du_crtc_stop(rcrtc);
	rcar_du_crtc_put(rcrtc);

	spin_lock_irq(&crtc->dev->event_lock);
	if (crtc->state->event) {
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		crtc->state->event = NULL;
	}
	spin_unlock_irq(&crtc->dev->event_lock);

	rcrtc->initialized = false;
	rcrtc->outputs = 0;
}