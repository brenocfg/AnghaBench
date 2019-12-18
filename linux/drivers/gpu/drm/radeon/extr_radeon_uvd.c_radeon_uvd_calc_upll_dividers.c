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
typedef  unsigned int uint64_t ;
struct TYPE_3__ {unsigned int reference_freq; } ;
struct TYPE_4__ {TYPE_1__ spll; } ;
struct radeon_device {TYPE_2__ clock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  do_div (unsigned int,unsigned int) ; 
 unsigned int max (unsigned int,unsigned int) ; 
 unsigned int radeon_uvd_calc_upll_post_div (unsigned int,unsigned int,unsigned int,unsigned int) ; 

int radeon_uvd_calc_upll_dividers(struct radeon_device *rdev,
				  unsigned vclk, unsigned dclk,
				  unsigned vco_min, unsigned vco_max,
				  unsigned fb_factor, unsigned fb_mask,
				  unsigned pd_min, unsigned pd_max,
				  unsigned pd_even,
				  unsigned *optimal_fb_div,
				  unsigned *optimal_vclk_div,
				  unsigned *optimal_dclk_div)
{
	unsigned vco_freq, ref_freq = rdev->clock.spll.reference_freq;

	/* start off with something large */
	unsigned optimal_score = ~0;

	/* loop through vco from low to high */
	vco_min = max(max(vco_min, vclk), dclk);
	for (vco_freq = vco_min; vco_freq <= vco_max; vco_freq += 100) {

		uint64_t fb_div = (uint64_t)vco_freq * fb_factor;
		unsigned vclk_div, dclk_div, score;

		do_div(fb_div, ref_freq);

		/* fb div out of range ? */
		if (fb_div > fb_mask)
			break; /* it can oly get worse */

		fb_div &= fb_mask;

		/* calc vclk divider with current vco freq */
		vclk_div = radeon_uvd_calc_upll_post_div(vco_freq, vclk,
							 pd_min, pd_even);
		if (vclk_div > pd_max)
			break; /* vco is too big, it has to stop */

		/* calc dclk divider with current vco freq */
		dclk_div = radeon_uvd_calc_upll_post_div(vco_freq, dclk,
							 pd_min, pd_even);
		if (dclk_div > pd_max)
			break; /* vco is too big, it has to stop */

		/* calc score with current vco freq */
		score = vclk - (vco_freq / vclk_div) + dclk - (vco_freq / dclk_div);

		/* determine if this vco setting is better than current optimal settings */
		if (score < optimal_score) {
			*optimal_fb_div = fb_div;
			*optimal_vclk_div = vclk_div;
			*optimal_dclk_div = dclk_div;
			optimal_score = score;
			if (optimal_score == 0)
				break; /* it can't get better than this */
		}
	}

	/* did we found a valid setup ? */
	if (optimal_score == ~0)
		return -EINVAL;

	return 0;
}