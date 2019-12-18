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
struct intel_encoder {int /*<<< orphan*/  port; } ;
struct intel_crtc_state {struct icl_port_dpll* icl_port_dplls; } ;
struct intel_crtc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_atomic_state {TYPE_1__ base; } ;
struct icl_port_dpll {void* pll; int /*<<< orphan*/  hw_state; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;

/* Variables and functions */
 int DPLL_ID_ICL_TBTPLL ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 size_t ICL_PORT_DPLL_DEFAULT ; 
 size_t ICL_PORT_DPLL_MG_PHY ; 
 int /*<<< orphan*/  icl_calc_dpll_state (struct intel_crtc_state*,struct intel_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  icl_calc_mg_pll_state (struct intel_crtc_state*,int /*<<< orphan*/ *) ; 
 int icl_tc_port_to_pll_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icl_update_active_dpll (struct intel_atomic_state*,struct intel_crtc*,struct intel_encoder*) ; 
 struct intel_crtc_state* intel_atomic_get_new_crtc_state (struct intel_atomic_state*,struct intel_crtc*) ; 
 void* intel_find_shared_dpll (struct intel_atomic_state*,struct intel_crtc*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  intel_port_to_tc (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_reference_shared_dpll (struct intel_atomic_state*,struct intel_crtc*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_unreference_shared_dpll (struct intel_atomic_state*,struct intel_crtc*,void*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool icl_get_tc_phy_dplls(struct intel_atomic_state *state,
				 struct intel_crtc *crtc,
				 struct intel_encoder *encoder)
{
	struct drm_i915_private *dev_priv = to_i915(state->base.dev);
	struct intel_crtc_state *crtc_state =
		intel_atomic_get_new_crtc_state(state, crtc);
	struct icl_port_dpll *port_dpll;
	enum intel_dpll_id dpll_id;

	port_dpll = &crtc_state->icl_port_dplls[ICL_PORT_DPLL_DEFAULT];
	if (!icl_calc_dpll_state(crtc_state, encoder, &port_dpll->hw_state)) {
		DRM_DEBUG_KMS("Could not calculate TBT PLL state.\n");
		return false;
	}

	port_dpll->pll = intel_find_shared_dpll(state, crtc,
						&port_dpll->hw_state,
						DPLL_ID_ICL_TBTPLL,
						DPLL_ID_ICL_TBTPLL);
	if (!port_dpll->pll) {
		DRM_DEBUG_KMS("No TBT-ALT PLL found\n");
		return false;
	}
	intel_reference_shared_dpll(state, crtc,
				    port_dpll->pll, &port_dpll->hw_state);


	port_dpll = &crtc_state->icl_port_dplls[ICL_PORT_DPLL_MG_PHY];
	if (!icl_calc_mg_pll_state(crtc_state, &port_dpll->hw_state)) {
		DRM_DEBUG_KMS("Could not calculate MG PHY PLL state.\n");
		goto err_unreference_tbt_pll;
	}

	dpll_id = icl_tc_port_to_pll_id(intel_port_to_tc(dev_priv,
							 encoder->port));
	port_dpll->pll = intel_find_shared_dpll(state, crtc,
						&port_dpll->hw_state,
						dpll_id,
						dpll_id);
	if (!port_dpll->pll) {
		DRM_DEBUG_KMS("No MG PHY PLL found\n");
		goto err_unreference_tbt_pll;
	}
	intel_reference_shared_dpll(state, crtc,
				    port_dpll->pll, &port_dpll->hw_state);

	icl_update_active_dpll(state, crtc, encoder);

	return true;

err_unreference_tbt_pll:
	port_dpll = &crtc_state->icl_port_dplls[ICL_PORT_DPLL_DEFAULT];
	intel_unreference_shared_dpll(state, crtc, port_dpll->pll);

	return false;
}