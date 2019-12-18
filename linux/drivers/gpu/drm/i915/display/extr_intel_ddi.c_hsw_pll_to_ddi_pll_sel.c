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
struct TYPE_2__ {int id; } ;

/* Variables and functions */
#define  DPLL_ID_LCPLL_1350 133 
#define  DPLL_ID_LCPLL_2700 132 
#define  DPLL_ID_LCPLL_810 131 
#define  DPLL_ID_SPLL 130 
#define  DPLL_ID_WRPLL1 129 
#define  DPLL_ID_WRPLL2 128 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int /*<<< orphan*/  PORT_CLK_SEL_LCPLL_1350 ; 
 int /*<<< orphan*/  PORT_CLK_SEL_LCPLL_2700 ; 
 int /*<<< orphan*/  PORT_CLK_SEL_LCPLL_810 ; 
 int /*<<< orphan*/  PORT_CLK_SEL_NONE ; 
 int /*<<< orphan*/  PORT_CLK_SEL_SPLL ; 
 int /*<<< orphan*/  PORT_CLK_SEL_WRPLL1 ; 
 int /*<<< orphan*/  PORT_CLK_SEL_WRPLL2 ; 

__attribute__((used)) static u32 hsw_pll_to_ddi_pll_sel(const struct intel_shared_dpll *pll)
{
	switch (pll->info->id) {
	case DPLL_ID_WRPLL1:
		return PORT_CLK_SEL_WRPLL1;
	case DPLL_ID_WRPLL2:
		return PORT_CLK_SEL_WRPLL2;
	case DPLL_ID_SPLL:
		return PORT_CLK_SEL_SPLL;
	case DPLL_ID_LCPLL_810:
		return PORT_CLK_SEL_LCPLL_810;
	case DPLL_ID_LCPLL_1350:
		return PORT_CLK_SEL_LCPLL_1350;
	case DPLL_ID_LCPLL_2700:
		return PORT_CLK_SEL_LCPLL_2700;
	default:
		MISSING_CASE(pll->info->id);
		return PORT_CLK_SEL_NONE;
	}
}