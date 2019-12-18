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
typedef  int /*<<< orphan*/  u32 ;
struct intel_shared_dpll {TYPE_1__* info; } ;
struct intel_encoder {int dummy; } ;
struct intel_crtc_state {int port_clock; struct intel_shared_dpll* shared_dpll; } ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDI_CLK_SEL_MG ; 
 int /*<<< orphan*/  DDI_CLK_SEL_NONE ; 
 int /*<<< orphan*/  DDI_CLK_SEL_TBT_162 ; 
 int /*<<< orphan*/  DDI_CLK_SEL_TBT_270 ; 
 int /*<<< orphan*/  DDI_CLK_SEL_TBT_540 ; 
 int /*<<< orphan*/  DDI_CLK_SEL_TBT_810 ; 
#define  DPLL_ID_ICL_MGPLL1 132 
#define  DPLL_ID_ICL_MGPLL2 131 
#define  DPLL_ID_ICL_MGPLL3 130 
#define  DPLL_ID_ICL_MGPLL4 129 
#define  DPLL_ID_ICL_TBTPLL 128 
 int /*<<< orphan*/  MISSING_CASE (int const) ; 

__attribute__((used)) static u32 icl_pll_to_ddi_clk_sel(struct intel_encoder *encoder,
				  const struct intel_crtc_state *crtc_state)
{
	const struct intel_shared_dpll *pll = crtc_state->shared_dpll;
	int clock = crtc_state->port_clock;
	const enum intel_dpll_id id = pll->info->id;

	switch (id) {
	default:
		/*
		 * DPLL_ID_ICL_DPLL0 and DPLL_ID_ICL_DPLL1 should not be used
		 * here, so do warn if this get passed in
		 */
		MISSING_CASE(id);
		return DDI_CLK_SEL_NONE;
	case DPLL_ID_ICL_TBTPLL:
		switch (clock) {
		case 162000:
			return DDI_CLK_SEL_TBT_162;
		case 270000:
			return DDI_CLK_SEL_TBT_270;
		case 540000:
			return DDI_CLK_SEL_TBT_540;
		case 810000:
			return DDI_CLK_SEL_TBT_810;
		default:
			MISSING_CASE(clock);
			return DDI_CLK_SEL_NONE;
		}
	case DPLL_ID_ICL_MGPLL1:
	case DPLL_ID_ICL_MGPLL2:
	case DPLL_ID_ICL_MGPLL3:
	case DPLL_ID_ICL_MGPLL4:
		return DDI_CLK_SEL_MG;
	}
}