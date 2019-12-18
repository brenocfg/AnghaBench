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
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;
struct igp_ps {scalar_t__ sclk_high; scalar_t__ sclk_low; } ;
struct atom_clock_dividers {scalar_t__ ref_div; scalar_t__ post_div; scalar_t__ fb_div; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPUTE_ENGINE_PLL_PARAM ; 
 int EINVAL ; 
 int FORCE_FEEDBACK_DIV ; 
 int /*<<< orphan*/  FVTHROT_FBDIV_REG0 ; 
 int /*<<< orphan*/  FVTHROT_FBDIV_REG1 ; 
 int MAX_FEEDBACK_DIV (scalar_t__) ; 
 int MAX_FEEDBACK_DIV_MASK ; 
 int MIN_FEEDBACK_DIV (scalar_t__) ; 
 int MIN_FEEDBACK_DIV_MASK ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int,int) ; 
 int radeon_atom_get_clock_dividers (struct radeon_device*,int /*<<< orphan*/ ,scalar_t__,int,struct atom_clock_dividers*) ; 
 int /*<<< orphan*/  rs780_force_fbdiv (struct radeon_device*,scalar_t__) ; 
 struct igp_ps* rs780_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static int rs780_set_engine_clock_scaling(struct radeon_device *rdev,
					  struct radeon_ps *new_ps,
					  struct radeon_ps *old_ps)
{
	struct atom_clock_dividers min_dividers, max_dividers, current_max_dividers;
	struct igp_ps *new_state = rs780_get_ps(new_ps);
	struct igp_ps *old_state = rs780_get_ps(old_ps);
	int ret;

	if ((new_state->sclk_high == old_state->sclk_high) &&
	    (new_state->sclk_low == old_state->sclk_low))
		return 0;

	ret = radeon_atom_get_clock_dividers(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     new_state->sclk_low, false, &min_dividers);
	if (ret)
		return ret;

	ret = radeon_atom_get_clock_dividers(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     new_state->sclk_high, false, &max_dividers);
	if (ret)
		return ret;

	ret = radeon_atom_get_clock_dividers(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     old_state->sclk_high, false, &current_max_dividers);
	if (ret)
		return ret;

	if ((min_dividers.ref_div != max_dividers.ref_div) ||
	    (min_dividers.post_div != max_dividers.post_div) ||
	    (max_dividers.ref_div != current_max_dividers.ref_div) ||
	    (max_dividers.post_div != current_max_dividers.post_div))
		return -EINVAL;

	rs780_force_fbdiv(rdev, max_dividers.fb_div);

	if (max_dividers.fb_div > min_dividers.fb_div) {
		WREG32_P(FVTHROT_FBDIV_REG0,
			 MIN_FEEDBACK_DIV(min_dividers.fb_div) |
			 MAX_FEEDBACK_DIV(max_dividers.fb_div),
			 ~(MIN_FEEDBACK_DIV_MASK | MAX_FEEDBACK_DIV_MASK));

		WREG32_P(FVTHROT_FBDIV_REG1, 0, ~FORCE_FEEDBACK_DIV);
	}

	return 0;
}