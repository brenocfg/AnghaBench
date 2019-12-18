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
typedef  int u32 ;
struct intel_dpll_hw_state {int cfgcr2; int cfgcr1; } ;

/* Variables and functions */
 int DPLL_CFGCR1_DCO_FRACTION_MASK ; 
 int DPLL_CFGCR1_DCO_INTEGER_MASK ; 
#define  DPLL_CFGCR2_KDIV_1 135 
#define  DPLL_CFGCR2_KDIV_2 134 
#define  DPLL_CFGCR2_KDIV_3 133 
#define  DPLL_CFGCR2_KDIV_5 132 
 int DPLL_CFGCR2_KDIV_MASK ; 
#define  DPLL_CFGCR2_PDIV_1 131 
#define  DPLL_CFGCR2_PDIV_2 130 
#define  DPLL_CFGCR2_PDIV_3 129 
#define  DPLL_CFGCR2_PDIV_7 128 
 int DPLL_CFGCR2_PDIV_MASK ; 
 int DPLL_CFGCR2_QDIV_MODE (int) ; 
 int DPLL_CFGCR2_QDIV_RATIO_MASK ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static int skl_calc_wrpll_link(const struct intel_dpll_hw_state *pll_state)
{
	u32 p0, p1, p2, dco_freq;

	p0 = pll_state->cfgcr2 & DPLL_CFGCR2_PDIV_MASK;
	p2 = pll_state->cfgcr2 & DPLL_CFGCR2_KDIV_MASK;

	if (pll_state->cfgcr2 &  DPLL_CFGCR2_QDIV_MODE(1))
		p1 = (pll_state->cfgcr2 & DPLL_CFGCR2_QDIV_RATIO_MASK) >> 8;
	else
		p1 = 1;


	switch (p0) {
	case DPLL_CFGCR2_PDIV_1:
		p0 = 1;
		break;
	case DPLL_CFGCR2_PDIV_2:
		p0 = 2;
		break;
	case DPLL_CFGCR2_PDIV_3:
		p0 = 3;
		break;
	case DPLL_CFGCR2_PDIV_7:
		p0 = 7;
		break;
	}

	switch (p2) {
	case DPLL_CFGCR2_KDIV_5:
		p2 = 5;
		break;
	case DPLL_CFGCR2_KDIV_2:
		p2 = 2;
		break;
	case DPLL_CFGCR2_KDIV_3:
		p2 = 3;
		break;
	case DPLL_CFGCR2_KDIV_1:
		p2 = 1;
		break;
	}

	dco_freq = (pll_state->cfgcr1 & DPLL_CFGCR1_DCO_INTEGER_MASK)
		* 24 * 1000;

	dco_freq += (((pll_state->cfgcr1 & DPLL_CFGCR1_DCO_FRACTION_MASK) >> 9)
		     * 24 * 1000) / 0x8000;

	if (WARN_ON(p0 == 0 || p1 == 0 || p2 == 0))
		return 0;

	return dco_freq / (p0 * p1 * p2 * 5);
}