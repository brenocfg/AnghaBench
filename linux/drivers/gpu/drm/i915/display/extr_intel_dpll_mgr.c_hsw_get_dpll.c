#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_shared_dpll {int dummy; } ;
struct intel_encoder {int dummy; } ;
struct TYPE_4__ {int spll; } ;
struct intel_crtc_state {int port_clock; struct intel_shared_dpll* shared_dpll; TYPE_1__ dpll_hw_state; } ;
struct intel_crtc {int dummy; } ;
struct intel_atomic_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPLL_ID_SPLL ; 
 int /*<<< orphan*/  INTEL_OUTPUT_ANALOG ; 
 int /*<<< orphan*/  INTEL_OUTPUT_HDMI ; 
 int SPLL_FREQ_1350MHz ; 
 int SPLL_PLL_ENABLE ; 
 int SPLL_REF_MUXED_SSC ; 
 scalar_t__ WARN_ON (int) ; 
 struct intel_shared_dpll* hsw_ddi_dp_get_dpll (struct intel_crtc_state*) ; 
 struct intel_shared_dpll* hsw_ddi_hdmi_get_dpll (struct intel_atomic_state*,struct intel_crtc*) ; 
 struct intel_crtc_state* intel_atomic_get_new_crtc_state (struct intel_atomic_state*,struct intel_crtc*) ; 
 scalar_t__ intel_crtc_has_dp_encoder (struct intel_crtc_state*) ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 struct intel_shared_dpll* intel_find_shared_dpll (struct intel_atomic_state*,struct intel_crtc*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_reference_shared_dpll (struct intel_atomic_state*,struct intel_crtc*,struct intel_shared_dpll*,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool hsw_get_dpll(struct intel_atomic_state *state,
			 struct intel_crtc *crtc,
			 struct intel_encoder *encoder)
{
	struct intel_crtc_state *crtc_state =
		intel_atomic_get_new_crtc_state(state, crtc);
	struct intel_shared_dpll *pll;

	memset(&crtc_state->dpll_hw_state, 0,
	       sizeof(crtc_state->dpll_hw_state));

	if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI)) {
		pll = hsw_ddi_hdmi_get_dpll(state, crtc);
	} else if (intel_crtc_has_dp_encoder(crtc_state)) {
		pll = hsw_ddi_dp_get_dpll(crtc_state);
	} else if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_ANALOG)) {
		if (WARN_ON(crtc_state->port_clock / 2 != 135000))
			return false;

		crtc_state->dpll_hw_state.spll =
			SPLL_PLL_ENABLE | SPLL_FREQ_1350MHz | SPLL_REF_MUXED_SSC;

		pll = intel_find_shared_dpll(state, crtc,
					     &crtc_state->dpll_hw_state,
					     DPLL_ID_SPLL, DPLL_ID_SPLL);
	} else {
		return false;
	}

	if (!pll)
		return false;

	intel_reference_shared_dpll(state, crtc,
				    pll, &crtc_state->dpll_hw_state);

	crtc_state->shared_dpll = pll;

	return true;
}