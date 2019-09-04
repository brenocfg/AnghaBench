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
struct radeon_pll {int flags; unsigned int min_feedback_div; unsigned int max_feedback_div; unsigned int reference_div; unsigned int min_ref_div; unsigned int max_ref_div; unsigned int post_div; unsigned int lcd_pll_out_min; unsigned int lcd_pll_out_max; unsigned int pll_out_min; unsigned int pll_out_max; unsigned int min_post_div; unsigned int max_post_div; unsigned int reference_freq; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int,int,int,unsigned int,unsigned int) ; 
 int RADEON_PLL_IS_LCD ; 
 int RADEON_PLL_PREFER_MINM_OVER_MAXP ; 
 int RADEON_PLL_USE_FRAC_FB_DIV ; 
 int RADEON_PLL_USE_POST_DIV ; 
 int RADEON_PLL_USE_REF_DIV ; 
 unsigned int abs (unsigned int) ; 
 int /*<<< orphan*/  avivo_get_fb_ref_div (unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  avivo_reduce_ratio (unsigned int*,unsigned int*,unsigned int,unsigned int) ; 
 unsigned int max (unsigned int,int) ; 
 unsigned int min (unsigned int,unsigned int) ; 

void radeon_compute_pll_avivo(struct radeon_pll *pll,
			      u32 freq,
			      u32 *dot_clock_p,
			      u32 *fb_div_p,
			      u32 *frac_fb_div_p,
			      u32 *ref_div_p,
			      u32 *post_div_p)
{
	unsigned target_clock = pll->flags & RADEON_PLL_USE_FRAC_FB_DIV ?
		freq : freq / 10;

	unsigned fb_div_min, fb_div_max, fb_div;
	unsigned post_div_min, post_div_max, post_div;
	unsigned ref_div_min, ref_div_max, ref_div;
	unsigned post_div_best, diff_best;
	unsigned nom, den;

	/* determine allowed feedback divider range */
	fb_div_min = pll->min_feedback_div;
	fb_div_max = pll->max_feedback_div;

	if (pll->flags & RADEON_PLL_USE_FRAC_FB_DIV) {
		fb_div_min *= 10;
		fb_div_max *= 10;
	}

	/* determine allowed ref divider range */
	if (pll->flags & RADEON_PLL_USE_REF_DIV)
		ref_div_min = pll->reference_div;
	else
		ref_div_min = pll->min_ref_div;

	if (pll->flags & RADEON_PLL_USE_FRAC_FB_DIV &&
	    pll->flags & RADEON_PLL_USE_REF_DIV)
		ref_div_max = pll->reference_div;
	else if (pll->flags & RADEON_PLL_PREFER_MINM_OVER_MAXP)
		/* fix for problems on RS880 */
		ref_div_max = min(pll->max_ref_div, 7u);
	else
		ref_div_max = pll->max_ref_div;

	/* determine allowed post divider range */
	if (pll->flags & RADEON_PLL_USE_POST_DIV) {
		post_div_min = pll->post_div;
		post_div_max = pll->post_div;
	} else {
		unsigned vco_min, vco_max;

		if (pll->flags & RADEON_PLL_IS_LCD) {
			vco_min = pll->lcd_pll_out_min;
			vco_max = pll->lcd_pll_out_max;
		} else {
			vco_min = pll->pll_out_min;
			vco_max = pll->pll_out_max;
		}

		if (pll->flags & RADEON_PLL_USE_FRAC_FB_DIV) {
			vco_min *= 10;
			vco_max *= 10;
		}

		post_div_min = vco_min / target_clock;
		if ((target_clock * post_div_min) < vco_min)
			++post_div_min;
		if (post_div_min < pll->min_post_div)
			post_div_min = pll->min_post_div;

		post_div_max = vco_max / target_clock;
		if ((target_clock * post_div_max) > vco_max)
			--post_div_max;
		if (post_div_max > pll->max_post_div)
			post_div_max = pll->max_post_div;
	}

	/* represent the searched ratio as fractional number */
	nom = target_clock;
	den = pll->reference_freq;

	/* reduce the numbers to a simpler ratio */
	avivo_reduce_ratio(&nom, &den, fb_div_min, post_div_min);

	/* now search for a post divider */
	if (pll->flags & RADEON_PLL_PREFER_MINM_OVER_MAXP)
		post_div_best = post_div_min;
	else
		post_div_best = post_div_max;
	diff_best = ~0;

	for (post_div = post_div_min; post_div <= post_div_max; ++post_div) {
		unsigned diff;
		avivo_get_fb_ref_div(nom, den, post_div, fb_div_max,
				     ref_div_max, &fb_div, &ref_div);
		diff = abs(target_clock - (pll->reference_freq * fb_div) /
			(ref_div * post_div));

		if (diff < diff_best || (diff == diff_best &&
		    !(pll->flags & RADEON_PLL_PREFER_MINM_OVER_MAXP))) {

			post_div_best = post_div;
			diff_best = diff;
		}
	}
	post_div = post_div_best;

	/* get the feedback and reference divider for the optimal value */
	avivo_get_fb_ref_div(nom, den, post_div, fb_div_max, ref_div_max,
			     &fb_div, &ref_div);

	/* reduce the numbers to a simpler ratio once more */
	/* this also makes sure that the reference divider is large enough */
	avivo_reduce_ratio(&fb_div, &ref_div, fb_div_min, ref_div_min);

	/* avoid high jitter with small fractional dividers */
	if (pll->flags & RADEON_PLL_USE_FRAC_FB_DIV && (fb_div % 10)) {
		fb_div_min = max(fb_div_min, (9 - (fb_div % 10)) * 20 + 50);
		if (fb_div < fb_div_min) {
			unsigned tmp = DIV_ROUND_UP(fb_div_min, fb_div);
			fb_div *= tmp;
			ref_div *= tmp;
		}
	}

	/* and finally save the result */
	if (pll->flags & RADEON_PLL_USE_FRAC_FB_DIV) {
		*fb_div_p = fb_div / 10;
		*frac_fb_div_p = fb_div % 10;
	} else {
		*fb_div_p = fb_div;
		*frac_fb_div_p = 0;
	}

	*dot_clock_p = ((pll->reference_freq * *fb_div_p * 10) +
			(pll->reference_freq * *frac_fb_div_p)) /
		       (ref_div * post_div * 10);
	*ref_div_p = ref_div;
	*post_div_p = post_div;

	DRM_DEBUG_KMS("%d - %d, pll dividers - fb: %d.%d ref: %d, post %d\n",
		      freq, *dot_clock_p * 10, *fb_div_p, *frac_fb_div_p,
		      ref_div, post_div);
}