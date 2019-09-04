#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct skl_wrpll_params {int dco_integer; int dco_fraction; int pdiv; int kdiv; int qdiv_mode; int qdiv_ratio; } ;
struct TYPE_3__ {int ref; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;
struct drm_i915_private {TYPE_2__ cdclk; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct skl_wrpll_params*) ; 
 int DPLL_CFGCR0_DCO_FRACTION_MASK ; 
 int DPLL_CFGCR0_DCO_FRACTION_SHIFT ; 
 int DPLL_CFGCR0_DCO_INTEGER_MASK ; 
 int DPLL_CFGCR1_KDIV_MASK ; 
 int DPLL_CFGCR1_KDIV_SHIFT ; 
 int DPLL_CFGCR1_PDIV_MASK ; 
 int DPLL_CFGCR1_PDIV_SHIFT ; 
 int DPLL_CFGCR1_QDIV_MODE (int) ; 
 int DPLL_CFGCR1_QDIV_MODE_SHIFT ; 
 int DPLL_CFGCR1_QDIV_RATIO_MASK ; 
 int DPLL_CFGCR1_QDIV_RATIO_SHIFT ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICL_DPLL_CFGCR0 (int) ; 
 int /*<<< orphan*/  ICL_DPLL_CFGCR1 (int) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 struct skl_wrpll_params* icl_dp_combo_pll_19_2MHz_values ; 
 struct skl_wrpll_params* icl_dp_combo_pll_24MHz_values ; 

int icl_calc_dp_combo_pll_link(struct drm_i915_private *dev_priv,
			       uint32_t pll_id)
{
	uint32_t cfgcr0, cfgcr1;
	uint32_t pdiv, kdiv, qdiv_mode, qdiv_ratio, dco_integer, dco_fraction;
	const struct skl_wrpll_params *params;
	int index, n_entries, link_clock;

	/* Read back values from DPLL CFGCR registers */
	cfgcr0 = I915_READ(ICL_DPLL_CFGCR0(pll_id));
	cfgcr1 = I915_READ(ICL_DPLL_CFGCR1(pll_id));

	dco_integer = cfgcr0 & DPLL_CFGCR0_DCO_INTEGER_MASK;
	dco_fraction = (cfgcr0 & DPLL_CFGCR0_DCO_FRACTION_MASK) >>
		DPLL_CFGCR0_DCO_FRACTION_SHIFT;
	pdiv = (cfgcr1 & DPLL_CFGCR1_PDIV_MASK) >> DPLL_CFGCR1_PDIV_SHIFT;
	kdiv = (cfgcr1 & DPLL_CFGCR1_KDIV_MASK) >> DPLL_CFGCR1_KDIV_SHIFT;
	qdiv_mode = (cfgcr1 & DPLL_CFGCR1_QDIV_MODE(1)) >>
		DPLL_CFGCR1_QDIV_MODE_SHIFT;
	qdiv_ratio = (cfgcr1 & DPLL_CFGCR1_QDIV_RATIO_MASK) >>
		DPLL_CFGCR1_QDIV_RATIO_SHIFT;

	params = dev_priv->cdclk.hw.ref == 24000 ?
		icl_dp_combo_pll_24MHz_values :
		icl_dp_combo_pll_19_2MHz_values;
	n_entries = ARRAY_SIZE(icl_dp_combo_pll_24MHz_values);

	for (index = 0; index < n_entries; index++) {
		if (dco_integer == params[index].dco_integer &&
		    dco_fraction == params[index].dco_fraction &&
		    pdiv == params[index].pdiv &&
		    kdiv == params[index].kdiv &&
		    qdiv_mode == params[index].qdiv_mode &&
		    qdiv_ratio == params[index].qdiv_ratio)
			break;
	}

	/* Map PLL Index to Link Clock */
	switch (index) {
	default:
		MISSING_CASE(index);
		/* fall through */
	case 0:
		link_clock = 540000;
		break;
	case 1:
		link_clock = 270000;
		break;
	case 2:
		link_clock = 162000;
		break;
	case 3:
		link_clock = 324000;
		break;
	case 4:
		link_clock = 216000;
		break;
	case 5:
		link_clock = 432000;
		break;
	case 6:
		link_clock = 648000;
		break;
	case 7:
		link_clock = 810000;
		break;
	}

	return link_clock;
}