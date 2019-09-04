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
struct intel_shared_dpll {int dummy; } ;
struct intel_encoder {int dummy; } ;
struct TYPE_2__ {int spll; } ;
struct intel_crtc_state {int port_clock; TYPE_1__ dpll_hw_state; } ;
struct intel_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPLL_ID_SPLL ; 
 int /*<<< orphan*/  INTEL_OUTPUT_ANALOG ; 
 int /*<<< orphan*/  INTEL_OUTPUT_HDMI ; 
 int SPLL_PLL_ENABLE ; 
 int SPLL_PLL_FREQ_1350MHz ; 
 int SPLL_PLL_SSC ; 
 scalar_t__ WARN_ON (int) ; 
 struct intel_shared_dpll* hsw_ddi_dp_get_dpll (struct intel_encoder*,int) ; 
 struct intel_shared_dpll* hsw_ddi_hdmi_get_dpll (int,struct intel_crtc*,struct intel_crtc_state*) ; 
 scalar_t__ intel_crtc_has_dp_encoder (struct intel_crtc_state*) ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 struct intel_shared_dpll* intel_find_shared_dpll (struct intel_crtc*,struct intel_crtc_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_reference_shared_dpll (struct intel_shared_dpll*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct intel_shared_dpll *
hsw_get_dpll(struct intel_crtc *crtc, struct intel_crtc_state *crtc_state,
	     struct intel_encoder *encoder)
{
	struct intel_shared_dpll *pll;
	int clock = crtc_state->port_clock;

	memset(&crtc_state->dpll_hw_state, 0,
	       sizeof(crtc_state->dpll_hw_state));

	if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI)) {
		pll = hsw_ddi_hdmi_get_dpll(clock, crtc, crtc_state);
	} else if (intel_crtc_has_dp_encoder(crtc_state)) {
		pll = hsw_ddi_dp_get_dpll(encoder, clock);
	} else if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_ANALOG)) {
		if (WARN_ON(crtc_state->port_clock / 2 != 135000))
			return NULL;

		crtc_state->dpll_hw_state.spll =
			SPLL_PLL_ENABLE | SPLL_PLL_FREQ_1350MHz | SPLL_PLL_SSC;

		pll = intel_find_shared_dpll(crtc, crtc_state,
					     DPLL_ID_SPLL, DPLL_ID_SPLL);
	} else {
		return NULL;
	}

	if (!pll)
		return NULL;

	intel_reference_shared_dpll(pll, crtc_state);

	return pll;
}