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
struct intel_encoder {int port; } ;
struct intel_dpll_hw_state {int dummy; } ;
struct intel_crtc_state {int port_clock; struct intel_dpll_hw_state dpll_hw_state; } ;
struct intel_crtc {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;

/* Variables and functions */
 int DPLL_ID_ICL_DPLL0 ; 
 int DPLL_ID_ICL_DPLL1 ; 
 int DPLL_ID_ICL_TBTPLL ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
#define  PORT_A 133 
#define  PORT_B 132 
#define  PORT_C 131 
#define  PORT_D 130 
#define  PORT_E 129 
#define  PORT_F 128 
 int icl_calc_dpll_state (struct intel_crtc_state*,struct intel_encoder*,int,struct intel_dpll_hw_state*) ; 
 int icl_calc_mg_pll_state (struct intel_crtc_state*,struct intel_encoder*,int,struct intel_dpll_hw_state*) ; 
 int icl_port_to_mg_pll_id (int) ; 
 struct intel_shared_dpll* intel_find_shared_dpll (struct intel_crtc*,struct intel_crtc_state*,int,int) ; 
 int /*<<< orphan*/  intel_reference_shared_dpll (struct intel_shared_dpll*,struct intel_crtc_state*) ; 

__attribute__((used)) static struct intel_shared_dpll *
icl_get_dpll(struct intel_crtc *crtc, struct intel_crtc_state *crtc_state,
	     struct intel_encoder *encoder)
{
	struct intel_shared_dpll *pll;
	struct intel_dpll_hw_state pll_state = {};
	enum port port = encoder->port;
	enum intel_dpll_id min, max;
	int clock = crtc_state->port_clock;
	bool ret;

	switch (port) {
	case PORT_A:
	case PORT_B:
		min = DPLL_ID_ICL_DPLL0;
		max = DPLL_ID_ICL_DPLL1;
		ret = icl_calc_dpll_state(crtc_state, encoder, clock,
					  &pll_state);
		break;
	case PORT_C:
	case PORT_D:
	case PORT_E:
	case PORT_F:
		if (0 /* TODO: TBT PLLs */) {
			min = DPLL_ID_ICL_TBTPLL;
			max = min;
			ret = icl_calc_dpll_state(crtc_state, encoder, clock,
						  &pll_state);
		} else {
			min = icl_port_to_mg_pll_id(port);
			max = min;
			ret = icl_calc_mg_pll_state(crtc_state, encoder, clock,
						    &pll_state);
		}
		break;
	default:
		MISSING_CASE(port);
		return NULL;
	}

	if (!ret) {
		DRM_DEBUG_KMS("Could not calculate PLL state.\n");
		return NULL;
	}

	crtc_state->dpll_hw_state = pll_state;

	pll = intel_find_shared_dpll(crtc, crtc_state, min, max);
	if (!pll) {
		DRM_DEBUG_KMS("No PLL selected\n");
		return NULL;
	}

	intel_reference_shared_dpll(pll, crtc_state);

	return pll;
}