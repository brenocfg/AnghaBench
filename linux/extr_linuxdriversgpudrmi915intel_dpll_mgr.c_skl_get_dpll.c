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
struct intel_shared_dpll {int dummy; } ;
struct intel_encoder {int dummy; } ;
struct intel_dpll_hw_state {int dummy; } ;
struct intel_crtc_state {int port_clock; struct intel_dpll_hw_state dpll_hw_state; } ;
struct intel_crtc {int dummy; } ;
typedef  int /*<<< orphan*/  dpll_hw_state ;

/* Variables and functions */
 int /*<<< orphan*/  DPLL_ID_SKL_DPLL0 ; 
 int /*<<< orphan*/  DPLL_ID_SKL_DPLL1 ; 
 int /*<<< orphan*/  DPLL_ID_SKL_DPLL3 ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_EDP ; 
 int /*<<< orphan*/  INTEL_OUTPUT_HDMI ; 
 scalar_t__ intel_crtc_has_dp_encoder (struct intel_crtc_state*) ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 struct intel_shared_dpll* intel_find_shared_dpll (struct intel_crtc*,struct intel_crtc_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_reference_shared_dpll (struct intel_shared_dpll*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  memset (struct intel_dpll_hw_state*,int /*<<< orphan*/ ,int) ; 
 int skl_ddi_dp_set_dpll_hw_state (int,struct intel_dpll_hw_state*) ; 
 int skl_ddi_hdmi_pll_dividers (struct intel_crtc*,struct intel_crtc_state*,int) ; 

__attribute__((used)) static struct intel_shared_dpll *
skl_get_dpll(struct intel_crtc *crtc, struct intel_crtc_state *crtc_state,
	     struct intel_encoder *encoder)
{
	struct intel_shared_dpll *pll;
	int clock = crtc_state->port_clock;
	bool bret;
	struct intel_dpll_hw_state dpll_hw_state;

	memset(&dpll_hw_state, 0, sizeof(dpll_hw_state));

	if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI)) {
		bret = skl_ddi_hdmi_pll_dividers(crtc, crtc_state, clock);
		if (!bret) {
			DRM_DEBUG_KMS("Could not get HDMI pll dividers.\n");
			return NULL;
		}
	} else if (intel_crtc_has_dp_encoder(crtc_state)) {
		bret = skl_ddi_dp_set_dpll_hw_state(clock, &dpll_hw_state);
		if (!bret) {
			DRM_DEBUG_KMS("Could not set DP dpll HW state.\n");
			return NULL;
		}
		crtc_state->dpll_hw_state = dpll_hw_state;
	} else {
		return NULL;
	}

	if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_EDP))
		pll = intel_find_shared_dpll(crtc, crtc_state,
					     DPLL_ID_SKL_DPLL0,
					     DPLL_ID_SKL_DPLL0);
	else
		pll = intel_find_shared_dpll(crtc, crtc_state,
					     DPLL_ID_SKL_DPLL1,
					     DPLL_ID_SKL_DPLL3);
	if (!pll)
		return NULL;

	intel_reference_shared_dpll(pll, crtc_state);

	return pll;
}