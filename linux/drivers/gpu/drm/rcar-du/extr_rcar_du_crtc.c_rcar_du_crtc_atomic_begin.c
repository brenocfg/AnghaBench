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
struct rcar_du_crtc {int /*<<< orphan*/  dev; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_1__* state; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCAR_DU_FEATURE_VSP1_SOURCE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  rcar_du_crtc_get (struct rcar_du_crtc*) ; 
 scalar_t__ rcar_du_has (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_du_vsp_atomic_begin (struct rcar_du_crtc*) ; 
 struct rcar_du_crtc* to_rcar_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void rcar_du_crtc_atomic_begin(struct drm_crtc *crtc,
				      struct drm_crtc_state *old_crtc_state)
{
	struct rcar_du_crtc *rcrtc = to_rcar_crtc(crtc);

	WARN_ON(!crtc->state->enable);

	/*
	 * If a mode set is in progress we can be called with the CRTC disabled.
	 * We thus need to first get and setup the CRTC in order to configure
	 * planes. We must *not* put the CRTC in .atomic_flush(), as it must be
	 * kept awake until the .atomic_enable() call that will follow. The get
	 * operation in .atomic_enable() will in that case be a no-op, and the
	 * CRTC will be put later in .atomic_disable().
	 *
	 * If a mode set is not in progress the CRTC is enabled, and the
	 * following get call will be a no-op. There is thus no need to balance
	 * it in .atomic_flush() either.
	 */
	rcar_du_crtc_get(rcrtc);

	if (rcar_du_has(rcrtc->dev, RCAR_DU_FEATURE_VSP1_SOURCE))
		rcar_du_vsp_atomic_begin(rcrtc);
}