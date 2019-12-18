#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  bridge; } ;
struct rcar_du_encoder {TYPE_2__ base; } ;
struct rcar_du_device {struct rcar_du_encoder** encoders; TYPE_1__* info; } ;
struct rcar_du_crtc_state {int outputs; } ;
struct rcar_du_crtc {size_t index; struct rcar_du_device* dev; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_4__* dev; TYPE_3__* state; } ;
struct TYPE_8__ {int /*<<< orphan*/  event_lock; } ;
struct TYPE_7__ {int /*<<< orphan*/ * event; } ;
struct TYPE_5__ {int lvds_clk_mask; } ;

/* Variables and functions */
 int BIT (size_t) ; 
 size_t RCAR_DU_OUTPUT_DPAD0 ; 
 size_t RCAR_DU_OUTPUT_LVDS0 ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcar_du_crtc_put (struct rcar_du_crtc*) ; 
 int /*<<< orphan*/  rcar_du_crtc_stop (struct rcar_du_crtc*) ; 
 int /*<<< orphan*/  rcar_lvds_clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct rcar_du_crtc* to_rcar_crtc (struct drm_crtc*) ; 
 struct rcar_du_crtc_state* to_rcar_crtc_state (struct drm_crtc_state*) ; 

__attribute__((used)) static void rcar_du_crtc_atomic_disable(struct drm_crtc *crtc,
					struct drm_crtc_state *old_state)
{
	struct rcar_du_crtc *rcrtc = to_rcar_crtc(crtc);
	struct rcar_du_crtc_state *rstate = to_rcar_crtc_state(old_state);
	struct rcar_du_device *rcdu = rcrtc->dev;

	rcar_du_crtc_stop(rcrtc);
	rcar_du_crtc_put(rcrtc);

	if (rcdu->info->lvds_clk_mask & BIT(rcrtc->index) &&
	    rstate->outputs == BIT(RCAR_DU_OUTPUT_DPAD0)) {
		struct rcar_du_encoder *encoder =
			rcdu->encoders[RCAR_DU_OUTPUT_LVDS0 + rcrtc->index];

		/*
		 * Disable the LVDS clock output, see
		 * rcar_du_crtc_atomic_enable().
		 */
		rcar_lvds_clk_disable(encoder->base.bridge);
	}

	spin_lock_irq(&crtc->dev->event_lock);
	if (crtc->state->event) {
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		crtc->state->event = NULL;
	}
	spin_unlock_irq(&crtc->dev->event_lock);
}