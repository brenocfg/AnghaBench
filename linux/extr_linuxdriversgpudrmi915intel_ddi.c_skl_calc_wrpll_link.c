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
typedef  int uint32_t ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;

/* Variables and functions */
 int /*<<< orphan*/  DPLL_CFGCR1 (int) ; 
 int DPLL_CFGCR1_DCO_FRACTION_MASK ; 
 int DPLL_CFGCR1_DCO_INTEGER_MASK ; 
 int /*<<< orphan*/  DPLL_CFGCR2 (int) ; 
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
 int I915_READ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skl_calc_wrpll_link(struct drm_i915_private *dev_priv,
			       enum intel_dpll_id pll_id)
{
	i915_reg_t cfgcr1_reg, cfgcr2_reg;
	uint32_t cfgcr1_val, cfgcr2_val;
	uint32_t p0, p1, p2, dco_freq;

	cfgcr1_reg = DPLL_CFGCR1(pll_id);
	cfgcr2_reg = DPLL_CFGCR2(pll_id);

	cfgcr1_val = I915_READ(cfgcr1_reg);
	cfgcr2_val = I915_READ(cfgcr2_reg);

	p0 = cfgcr2_val & DPLL_CFGCR2_PDIV_MASK;
	p2 = cfgcr2_val & DPLL_CFGCR2_KDIV_MASK;

	if (cfgcr2_val &  DPLL_CFGCR2_QDIV_MODE(1))
		p1 = (cfgcr2_val & DPLL_CFGCR2_QDIV_RATIO_MASK) >> 8;
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

	dco_freq = (cfgcr1_val & DPLL_CFGCR1_DCO_INTEGER_MASK) * 24 * 1000;

	dco_freq += (((cfgcr1_val & DPLL_CFGCR1_DCO_FRACTION_MASK) >> 9) * 24 *
		1000) / 0x8000;

	return dco_freq / (p0 * p1 * p2 * 5);
}