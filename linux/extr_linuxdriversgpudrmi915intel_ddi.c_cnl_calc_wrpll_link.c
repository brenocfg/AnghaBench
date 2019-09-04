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
struct TYPE_3__ {int ref; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;
struct drm_i915_private {TYPE_2__ cdclk; } ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;

/* Variables and functions */
 int /*<<< orphan*/  CNL_DPLL_CFGCR0 (int) ; 
 int /*<<< orphan*/  CNL_DPLL_CFGCR1 (int) ; 
 int DPLL_CFGCR0_DCO_FRACTION_MASK ; 
 int DPLL_CFGCR0_DCO_FRACTION_SHIFT ; 
 int DPLL_CFGCR0_DCO_INTEGER_MASK ; 
#define  DPLL_CFGCR1_KDIV_1 134 
#define  DPLL_CFGCR1_KDIV_2 133 
#define  DPLL_CFGCR1_KDIV_4 132 
 int DPLL_CFGCR1_KDIV_MASK ; 
#define  DPLL_CFGCR1_PDIV_2 131 
#define  DPLL_CFGCR1_PDIV_3 130 
#define  DPLL_CFGCR1_PDIV_5 129 
#define  DPLL_CFGCR1_PDIV_7 128 
 int DPLL_CFGCR1_PDIV_MASK ; 
 int DPLL_CFGCR1_QDIV_MODE (int) ; 
 int DPLL_CFGCR1_QDIV_RATIO_MASK ; 
 int DPLL_CFGCR1_QDIV_RATIO_SHIFT ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICL_DPLL_CFGCR0 (int) ; 
 int /*<<< orphan*/  ICL_DPLL_CFGCR1 (int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static int cnl_calc_wrpll_link(struct drm_i915_private *dev_priv,
			       enum intel_dpll_id pll_id)
{
	uint32_t cfgcr0, cfgcr1;
	uint32_t p0, p1, p2, dco_freq, ref_clock;

	if (INTEL_GEN(dev_priv) >= 11) {
		cfgcr0 = I915_READ(ICL_DPLL_CFGCR0(pll_id));
		cfgcr1 = I915_READ(ICL_DPLL_CFGCR1(pll_id));
	} else {
		cfgcr0 = I915_READ(CNL_DPLL_CFGCR0(pll_id));
		cfgcr1 = I915_READ(CNL_DPLL_CFGCR1(pll_id));
	}

	p0 = cfgcr1 & DPLL_CFGCR1_PDIV_MASK;
	p2 = cfgcr1 & DPLL_CFGCR1_KDIV_MASK;

	if (cfgcr1 & DPLL_CFGCR1_QDIV_MODE(1))
		p1 = (cfgcr1 & DPLL_CFGCR1_QDIV_RATIO_MASK) >>
			DPLL_CFGCR1_QDIV_RATIO_SHIFT;
	else
		p1 = 1;


	switch (p0) {
	case DPLL_CFGCR1_PDIV_2:
		p0 = 2;
		break;
	case DPLL_CFGCR1_PDIV_3:
		p0 = 3;
		break;
	case DPLL_CFGCR1_PDIV_5:
		p0 = 5;
		break;
	case DPLL_CFGCR1_PDIV_7:
		p0 = 7;
		break;
	}

	switch (p2) {
	case DPLL_CFGCR1_KDIV_1:
		p2 = 1;
		break;
	case DPLL_CFGCR1_KDIV_2:
		p2 = 2;
		break;
	case DPLL_CFGCR1_KDIV_4:
		p2 = 4;
		break;
	}

	ref_clock = dev_priv->cdclk.hw.ref;

	dco_freq = (cfgcr0 & DPLL_CFGCR0_DCO_INTEGER_MASK) * ref_clock;

	dco_freq += (((cfgcr0 & DPLL_CFGCR0_DCO_FRACTION_MASK) >>
		      DPLL_CFGCR0_DCO_FRACTION_SHIFT) * ref_clock) / 0x8000;

	if (WARN_ON(p0 == 0 || p1 == 0 || p2 == 0))
		return 0;

	return dco_freq / (p0 * p1 * p2 * 5);
}