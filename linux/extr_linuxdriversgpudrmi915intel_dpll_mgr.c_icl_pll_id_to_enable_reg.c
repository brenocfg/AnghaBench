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
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;

/* Variables and functions */
 int /*<<< orphan*/  CNL_DPLL_ENABLE (int) ; 
#define  DPLL_ID_ICL_DPLL0 134 
#define  DPLL_ID_ICL_DPLL1 133 
#define  DPLL_ID_ICL_MGPLL1 132 
#define  DPLL_ID_ICL_MGPLL2 131 
#define  DPLL_ID_ICL_MGPLL3 130 
#define  DPLL_ID_ICL_MGPLL4 129 
#define  DPLL_ID_ICL_TBTPLL 128 
 int /*<<< orphan*/  MG_PLL_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int /*<<< orphan*/  TBT_PLL_ENABLE ; 
 int /*<<< orphan*/  icl_mg_pll_id_to_port (int) ; 

__attribute__((used)) static i915_reg_t icl_pll_id_to_enable_reg(enum intel_dpll_id id)
{
	switch (id) {
	default:
		MISSING_CASE(id);
		/* fall through */
	case DPLL_ID_ICL_DPLL0:
	case DPLL_ID_ICL_DPLL1:
		return CNL_DPLL_ENABLE(id);
	case DPLL_ID_ICL_TBTPLL:
		return TBT_PLL_ENABLE;
	case DPLL_ID_ICL_MGPLL1:
	case DPLL_ID_ICL_MGPLL2:
	case DPLL_ID_ICL_MGPLL3:
	case DPLL_ID_ICL_MGPLL4:
		return MG_PLL_ENABLE(icl_mg_pll_id_to_port(id));
	}
}