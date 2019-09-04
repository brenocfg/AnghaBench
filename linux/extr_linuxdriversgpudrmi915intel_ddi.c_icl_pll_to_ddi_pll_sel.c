#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct intel_shared_dpll {TYPE_3__* info; } ;
struct TYPE_4__ {int /*<<< orphan*/  crtc; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct intel_crtc {TYPE_2__* config; } ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;
struct TYPE_6__ {int id; } ;
struct TYPE_5__ {int port_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDI_CLK_SEL_MG ; 
 int /*<<< orphan*/  DDI_CLK_SEL_NONE ; 
 int /*<<< orphan*/  DDI_CLK_SEL_TBT_162 ; 
 int /*<<< orphan*/  DDI_CLK_SEL_TBT_270 ; 
 int /*<<< orphan*/  DDI_CLK_SEL_TBT_540 ; 
 int /*<<< orphan*/  DDI_CLK_SEL_TBT_810 ; 
#define  DPLL_ID_ICL_DPLL0 134 
#define  DPLL_ID_ICL_DPLL1 133 
#define  DPLL_ID_ICL_MGPLL1 132 
#define  DPLL_ID_ICL_MGPLL2 131 
#define  DPLL_ID_ICL_MGPLL3 130 
#define  DPLL_ID_ICL_MGPLL4 129 
#define  DPLL_ID_ICL_TBTPLL 128 
 int /*<<< orphan*/  MISSING_CASE (int const) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t icl_pll_to_ddi_pll_sel(struct intel_encoder *encoder,
				       const struct intel_shared_dpll *pll)
{
	struct intel_crtc *crtc = to_intel_crtc(encoder->base.crtc);
	int clock = crtc->config->port_clock;
	const enum intel_dpll_id id = pll->info->id;

	switch (id) {
	default:
		MISSING_CASE(id);
		/* fall through */
	case DPLL_ID_ICL_DPLL0:
	case DPLL_ID_ICL_DPLL1:
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