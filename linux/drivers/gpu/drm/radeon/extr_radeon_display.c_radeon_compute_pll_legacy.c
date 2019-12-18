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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int u32 ;
struct radeon_pll {int min_ref_div; int max_ref_div; int min_post_div; int max_post_div; int best_vco; int flags; int lcd_pll_out_min; int lcd_pll_out_max; int pll_out_min; int pll_out_max; int reference_div; int reference_freq; int pll_in_min; int pll_in_max; int post_div; int min_frac_feedback_div; int max_frac_feedback_div; int min_feedback_div; int max_feedback_div; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,long long,int,int,...) ; 
 int RADEON_PLL_IS_LCD ; 
 int RADEON_PLL_LEGACY ; 
 int RADEON_PLL_NO_ODD_POST_DIV ; 
 int RADEON_PLL_PREFER_CLOSEST_LOWER ; 
 int RADEON_PLL_PREFER_HIGH_FB_DIV ; 
 int RADEON_PLL_PREFER_HIGH_POST_DIV ; 
 int RADEON_PLL_PREFER_HIGH_REF_DIV ; 
 int RADEON_PLL_PREFER_LOW_FB_DIV ; 
 int RADEON_PLL_PREFER_LOW_POST_DIV ; 
 int RADEON_PLL_PREFER_LOW_REF_DIV ; 
 int RADEON_PLL_USE_FRAC_FB_DIV ; 
 int RADEON_PLL_USE_POST_DIV ; 
 int RADEON_PLL_USE_REF_DIV ; 
 int abs (int) ; 
 int radeon_div (int,int) ; 

void radeon_compute_pll_legacy(struct radeon_pll *pll,
			       uint64_t freq,
			       uint32_t *dot_clock_p,
			       uint32_t *fb_div_p,
			       uint32_t *frac_fb_div_p,
			       uint32_t *ref_div_p,
			       uint32_t *post_div_p)
{
	uint32_t min_ref_div = pll->min_ref_div;
	uint32_t max_ref_div = pll->max_ref_div;
	uint32_t min_post_div = pll->min_post_div;
	uint32_t max_post_div = pll->max_post_div;
	uint32_t min_fractional_feed_div = 0;
	uint32_t max_fractional_feed_div = 0;
	uint32_t best_vco = pll->best_vco;
	uint32_t best_post_div = 1;
	uint32_t best_ref_div = 1;
	uint32_t best_feedback_div = 1;
	uint32_t best_frac_feedback_div = 0;
	uint32_t best_freq = -1;
	uint32_t best_error = 0xffffffff;
	uint32_t best_vco_diff = 1;
	uint32_t post_div;
	u32 pll_out_min, pll_out_max;

	DRM_DEBUG_KMS("PLL freq %llu %u %u\n", freq, pll->min_ref_div, pll->max_ref_div);
	freq = freq * 1000;

	if (pll->flags & RADEON_PLL_IS_LCD) {
		pll_out_min = pll->lcd_pll_out_min;
		pll_out_max = pll->lcd_pll_out_max;
	} else {
		pll_out_min = pll->pll_out_min;
		pll_out_max = pll->pll_out_max;
	}

	if (pll_out_min > 64800)
		pll_out_min = 64800;

	if (pll->flags & RADEON_PLL_USE_REF_DIV)
		min_ref_div = max_ref_div = pll->reference_div;
	else {
		while (min_ref_div < max_ref_div-1) {
			uint32_t mid = (min_ref_div + max_ref_div) / 2;
			uint32_t pll_in = pll->reference_freq / mid;
			if (pll_in < pll->pll_in_min)
				max_ref_div = mid;
			else if (pll_in > pll->pll_in_max)
				min_ref_div = mid;
			else
				break;
		}
	}

	if (pll->flags & RADEON_PLL_USE_POST_DIV)
		min_post_div = max_post_div = pll->post_div;

	if (pll->flags & RADEON_PLL_USE_FRAC_FB_DIV) {
		min_fractional_feed_div = pll->min_frac_feedback_div;
		max_fractional_feed_div = pll->max_frac_feedback_div;
	}

	for (post_div = max_post_div; post_div >= min_post_div; --post_div) {
		uint32_t ref_div;

		if ((pll->flags & RADEON_PLL_NO_ODD_POST_DIV) && (post_div & 1))
			continue;

		/* legacy radeons only have a few post_divs */
		if (pll->flags & RADEON_PLL_LEGACY) {
			if ((post_div == 5) ||
			    (post_div == 7) ||
			    (post_div == 9) ||
			    (post_div == 10) ||
			    (post_div == 11) ||
			    (post_div == 13) ||
			    (post_div == 14) ||
			    (post_div == 15))
				continue;
		}

		for (ref_div = min_ref_div; ref_div <= max_ref_div; ++ref_div) {
			uint32_t feedback_div, current_freq = 0, error, vco_diff;
			uint32_t pll_in = pll->reference_freq / ref_div;
			uint32_t min_feed_div = pll->min_feedback_div;
			uint32_t max_feed_div = pll->max_feedback_div + 1;

			if (pll_in < pll->pll_in_min || pll_in > pll->pll_in_max)
				continue;

			while (min_feed_div < max_feed_div) {
				uint32_t vco;
				uint32_t min_frac_feed_div = min_fractional_feed_div;
				uint32_t max_frac_feed_div = max_fractional_feed_div + 1;
				uint32_t frac_feedback_div;
				uint64_t tmp;

				feedback_div = (min_feed_div + max_feed_div) / 2;

				tmp = (uint64_t)pll->reference_freq * feedback_div;
				vco = radeon_div(tmp, ref_div);

				if (vco < pll_out_min) {
					min_feed_div = feedback_div + 1;
					continue;
				} else if (vco > pll_out_max) {
					max_feed_div = feedback_div;
					continue;
				}

				while (min_frac_feed_div < max_frac_feed_div) {
					frac_feedback_div = (min_frac_feed_div + max_frac_feed_div) / 2;
					tmp = (uint64_t)pll->reference_freq * 10000 * feedback_div;
					tmp += (uint64_t)pll->reference_freq * 1000 * frac_feedback_div;
					current_freq = radeon_div(tmp, ref_div * post_div);

					if (pll->flags & RADEON_PLL_PREFER_CLOSEST_LOWER) {
						if (freq < current_freq)
							error = 0xffffffff;
						else
							error = freq - current_freq;
					} else
						error = abs(current_freq - freq);
					vco_diff = abs(vco - best_vco);

					if ((best_vco == 0 && error < best_error) ||
					    (best_vco != 0 &&
					     ((best_error > 100 && error < best_error - 100) ||
					      (abs(error - best_error) < 100 && vco_diff < best_vco_diff)))) {
						best_post_div = post_div;
						best_ref_div = ref_div;
						best_feedback_div = feedback_div;
						best_frac_feedback_div = frac_feedback_div;
						best_freq = current_freq;
						best_error = error;
						best_vco_diff = vco_diff;
					} else if (current_freq == freq) {
						if (best_freq == -1) {
							best_post_div = post_div;
							best_ref_div = ref_div;
							best_feedback_div = feedback_div;
							best_frac_feedback_div = frac_feedback_div;
							best_freq = current_freq;
							best_error = error;
							best_vco_diff = vco_diff;
						} else if (((pll->flags & RADEON_PLL_PREFER_LOW_REF_DIV) && (ref_div < best_ref_div)) ||
							   ((pll->flags & RADEON_PLL_PREFER_HIGH_REF_DIV) && (ref_div > best_ref_div)) ||
							   ((pll->flags & RADEON_PLL_PREFER_LOW_FB_DIV) && (feedback_div < best_feedback_div)) ||
							   ((pll->flags & RADEON_PLL_PREFER_HIGH_FB_DIV) && (feedback_div > best_feedback_div)) ||
							   ((pll->flags & RADEON_PLL_PREFER_LOW_POST_DIV) && (post_div < best_post_div)) ||
							   ((pll->flags & RADEON_PLL_PREFER_HIGH_POST_DIV) && (post_div > best_post_div))) {
							best_post_div = post_div;
							best_ref_div = ref_div;
							best_feedback_div = feedback_div;
							best_frac_feedback_div = frac_feedback_div;
							best_freq = current_freq;
							best_error = error;
							best_vco_diff = vco_diff;
						}
					}
					if (current_freq < freq)
						min_frac_feed_div = frac_feedback_div + 1;
					else
						max_frac_feed_div = frac_feedback_div;
				}
				if (current_freq < freq)
					min_feed_div = feedback_div + 1;
				else
					max_feed_div = feedback_div;
			}
		}
	}

	*dot_clock_p = best_freq / 10000;
	*fb_div_p = best_feedback_div;
	*frac_fb_div_p = best_frac_feedback_div;
	*ref_div_p = best_ref_div;
	*post_div_p = best_post_div;
	DRM_DEBUG_KMS("%lld %d, pll dividers - fb: %d.%d ref: %d, post %d\n",
		      (long long)freq,
		      best_freq / 1000, best_feedback_div, best_frac_feedback_div,
		      best_ref_div, best_post_div);

}