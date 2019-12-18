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
struct drm_crtc {int dummy; } ;
struct rcar_du_crtc {int /*<<< orphan*/  group; int /*<<< orphan*/  dev; struct drm_crtc crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSYSR_TVM_MASK ; 
 int /*<<< orphan*/  DSYSR_TVM_SWITCH ; 
 int /*<<< orphan*/  RCAR_DU_FEATURE_TVM_SYNC ; 
 int /*<<< orphan*/  RCAR_DU_FEATURE_VSP1_SOURCE ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (struct drm_crtc*) ; 
 int /*<<< orphan*/  rcar_du_crtc_disable_planes (struct rcar_du_crtc*) ; 
 int /*<<< orphan*/  rcar_du_crtc_dsysr_clr_set (struct rcar_du_crtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_du_crtc_wait_page_flip (struct rcar_du_crtc*) ; 
 int /*<<< orphan*/  rcar_du_group_start_stop (int /*<<< orphan*/ ,int) ; 
 scalar_t__ rcar_du_has (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_du_vsp_disable (struct rcar_du_crtc*) ; 

__attribute__((used)) static void rcar_du_crtc_stop(struct rcar_du_crtc *rcrtc)
{
	struct drm_crtc *crtc = &rcrtc->crtc;

	/*
	 * Disable all planes and wait for the change to take effect. This is
	 * required as the plane enable registers are updated on vblank, and no
	 * vblank will occur once the CRTC is stopped. Disabling planes when
	 * starting the CRTC thus wouldn't be enough as it would start scanning
	 * out immediately from old frame buffers until the next vblank.
	 *
	 * This increases the CRTC stop delay, especially when multiple CRTCs
	 * are stopped in one operation as we now wait for one vblank per CRTC.
	 * Whether this can be improved needs to be researched.
	 */
	rcar_du_crtc_disable_planes(rcrtc);

	/*
	 * Disable vertical blanking interrupt reporting. We first need to wait
	 * for page flip completion before stopping the CRTC as userspace
	 * expects page flips to eventually complete.
	 */
	rcar_du_crtc_wait_page_flip(rcrtc);
	drm_crtc_vblank_off(crtc);

	/* Disable the VSP compositor. */
	if (rcar_du_has(rcrtc->dev, RCAR_DU_FEATURE_VSP1_SOURCE))
		rcar_du_vsp_disable(rcrtc);

	/*
	 * Select switch sync mode. This stops display operation and configures
	 * the HSYNC and VSYNC signals as inputs.
	 *
	 * TODO: Find another way to stop the display for DUs that don't support
	 * TVM sync.
	 */
	if (rcar_du_has(rcrtc->dev, RCAR_DU_FEATURE_TVM_SYNC))
		rcar_du_crtc_dsysr_clr_set(rcrtc, DSYSR_TVM_MASK,
					   DSYSR_TVM_SWITCH);

	rcar_du_group_start_stop(rcrtc->group, false);
}