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
typedef  int u64 ;
typedef  int u32 ;
struct hdmi_8996_post_divider {int vco_freq; int tx_band_sel; int vco_ratio; int hsclk_divsel; } ;

/* Variables and functions */
 int EINVAL ; 
 int HDMI_VCO_MAX_FREQ ; 
 int HDMI_VCO_MIN_FREQ ; 

__attribute__((used)) static int pll_get_post_div(struct hdmi_8996_post_divider *pd, u64 bclk)
{
	int ratio[] = { 2, 3, 4, 5, 6, 9, 10, 12, 14, 15, 20, 21, 25, 28, 35 };
	int hs_divsel[] = { 0, 4, 8, 12, 1, 5, 2, 9, 3, 13, 10, 7, 14, 11, 15 };
	int tx_band_sel[] = { 0, 1, 2, 3 };
	u64 vco_freq[60];
	u64 vco, vco_optimal;
	int half_rate_mode = 0;
	int vco_optimal_index, vco_freq_index;
	int i, j;

retry:
	vco_optimal = HDMI_VCO_MAX_FREQ;
	vco_optimal_index = -1;
	vco_freq_index = 0;
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 4; j++) {
			u32 ratio_mult = ratio[i] << tx_band_sel[j];

			vco = bclk >> half_rate_mode;
			vco *= ratio_mult;
			vco_freq[vco_freq_index++] = vco;
		}
	}

	for (i = 0; i < 60; i++) {
		u64 vco_tmp = vco_freq[i];

		if ((vco_tmp >= HDMI_VCO_MIN_FREQ) &&
		    (vco_tmp <= vco_optimal)) {
			vco_optimal = vco_tmp;
			vco_optimal_index = i;
		}
	}

	if (vco_optimal_index == -1) {
		if (!half_rate_mode) {
			half_rate_mode = 1;
			goto retry;
		}
	} else {
		pd->vco_freq = vco_optimal;
		pd->tx_band_sel = tx_band_sel[vco_optimal_index % 4];
		pd->vco_ratio = ratio[vco_optimal_index / 4];
		pd->hsclk_divsel = hs_divsel[vco_optimal_index / 4];

		return 0;
	}

	return -EINVAL;
}