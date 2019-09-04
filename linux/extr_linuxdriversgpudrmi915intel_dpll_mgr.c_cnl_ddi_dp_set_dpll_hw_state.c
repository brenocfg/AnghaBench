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
typedef  int /*<<< orphan*/  uint32_t ;
struct intel_dpll_hw_state {int /*<<< orphan*/  cfgcr0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPLL_CFGCR0_LINK_RATE_1080 ; 
 int /*<<< orphan*/  DPLL_CFGCR0_LINK_RATE_1350 ; 
 int /*<<< orphan*/  DPLL_CFGCR0_LINK_RATE_1620 ; 
 int /*<<< orphan*/  DPLL_CFGCR0_LINK_RATE_2160 ; 
 int /*<<< orphan*/  DPLL_CFGCR0_LINK_RATE_2700 ; 
 int /*<<< orphan*/  DPLL_CFGCR0_LINK_RATE_3240 ; 
 int /*<<< orphan*/  DPLL_CFGCR0_LINK_RATE_4050 ; 
 int /*<<< orphan*/  DPLL_CFGCR0_LINK_RATE_810 ; 
 int /*<<< orphan*/  DPLL_CFGCR0_SSC_ENABLE ; 

__attribute__((used)) static bool
cnl_ddi_dp_set_dpll_hw_state(int clock,
			     struct intel_dpll_hw_state *dpll_hw_state)
{
	uint32_t cfgcr0;

	cfgcr0 = DPLL_CFGCR0_SSC_ENABLE;

	switch (clock / 2) {
	case 81000:
		cfgcr0 |= DPLL_CFGCR0_LINK_RATE_810;
		break;
	case 135000:
		cfgcr0 |= DPLL_CFGCR0_LINK_RATE_1350;
		break;
	case 270000:
		cfgcr0 |= DPLL_CFGCR0_LINK_RATE_2700;
		break;
		/* eDP 1.4 rates */
	case 162000:
		cfgcr0 |= DPLL_CFGCR0_LINK_RATE_1620;
		break;
	case 108000:
		cfgcr0 |= DPLL_CFGCR0_LINK_RATE_1080;
		break;
	case 216000:
		cfgcr0 |= DPLL_CFGCR0_LINK_RATE_2160;
		break;
	case 324000:
		/* Some SKUs may require elevated I/O voltage to support this */
		cfgcr0 |= DPLL_CFGCR0_LINK_RATE_3240;
		break;
	case 405000:
		/* Some SKUs may require elevated I/O voltage to support this */
		cfgcr0 |= DPLL_CFGCR0_LINK_RATE_4050;
		break;
	}

	dpll_hw_state->cfgcr0 = cfgcr0;
	return true;
}