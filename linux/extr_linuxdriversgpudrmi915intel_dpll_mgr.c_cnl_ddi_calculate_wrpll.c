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
typedef  int u32 ;
struct skl_wrpll_params {int dummy; } ;
struct TYPE_3__ {int ref; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;
struct drm_i915_private {TYPE_2__ cdclk; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 scalar_t__ IS_ICELAKE (struct drm_i915_private*) ; 
 int U32_MAX ; 
 int abs (int) ; 
 int /*<<< orphan*/  cnl_wrpll_get_multipliers (int,int*,int*,int*) ; 
 int /*<<< orphan*/  cnl_wrpll_params_populate (struct skl_wrpll_params*,int,int,int,int,int) ; 

__attribute__((used)) static bool
cnl_ddi_calculate_wrpll(int clock,
			struct drm_i915_private *dev_priv,
			struct skl_wrpll_params *wrpll_params)
{
	u32 afe_clock = clock * 5;
	uint32_t ref_clock;
	u32 dco_min = 7998000;
	u32 dco_max = 10000000;
	u32 dco_mid = (dco_min + dco_max) / 2;
	static const int dividers[] = {  2,  4,  6,  8, 10, 12,  14,  16,
					 18, 20, 24, 28, 30, 32,  36,  40,
					 42, 44, 48, 50, 52, 54,  56,  60,
					 64, 66, 68, 70, 72, 76,  78,  80,
					 84, 88, 90, 92, 96, 98, 100, 102,
					  3,  5,  7,  9, 15, 21 };
	u32 dco, best_dco = 0, dco_centrality = 0;
	u32 best_dco_centrality = U32_MAX; /* Spec meaning of 999999 MHz */
	int d, best_div = 0, pdiv = 0, qdiv = 0, kdiv = 0;

	for (d = 0; d < ARRAY_SIZE(dividers); d++) {
		dco = afe_clock * dividers[d];

		if ((dco <= dco_max) && (dco >= dco_min)) {
			dco_centrality = abs(dco - dco_mid);

			if (dco_centrality < best_dco_centrality) {
				best_dco_centrality = dco_centrality;
				best_div = dividers[d];
				best_dco = dco;
			}
		}
	}

	if (best_div == 0)
		return false;

	cnl_wrpll_get_multipliers(best_div, &pdiv, &qdiv, &kdiv);

	ref_clock = dev_priv->cdclk.hw.ref;

	/*
	 * For ICL, the spec states: if reference frequency is 38.4, use 19.2
	 * because the DPLL automatically divides that by 2.
	 */
	if (IS_ICELAKE(dev_priv) && ref_clock == 38400)
		ref_clock = 19200;

	cnl_wrpll_params_populate(wrpll_params, best_dco, ref_clock, pdiv, qdiv,
				  kdiv);

	return true;
}