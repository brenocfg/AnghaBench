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
struct meson_mmc_phase {int delay_mask; int delay_step_ps; int /*<<< orphan*/  phase_mask; } ;
struct clk_hw {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_CLOSEST (unsigned long,int) ; 
 int DIV_ROUND_CLOSEST_ULL (int,int) ; 
 unsigned long DIV_ROUND_UP (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ NSEC_PER_SEC ; 
 int __ffs (int) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 unsigned long do_div (int,int) ; 
 int hweight_long (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_mmc_apply_phase_delay (struct meson_mmc_phase*,int,unsigned long) ; 
 unsigned long min (unsigned long,int) ; 
 struct meson_mmc_phase* to_meson_mmc_phase (struct clk_hw*) ; 

__attribute__((used)) static int meson_mmc_clk_set_phase(struct clk_hw *hw, int degrees)
{
	struct meson_mmc_phase *mmc = to_meson_mmc_phase(hw);
	unsigned int phase_num = 1 <<  hweight_long(mmc->phase_mask);
	unsigned long period_ps, d = 0, r;
	uint64_t p;

	p = degrees % 360;

	if (!mmc->delay_mask) {
		p = DIV_ROUND_CLOSEST_ULL(p, 360 / phase_num);
	} else {
		period_ps = DIV_ROUND_UP((unsigned long)NSEC_PER_SEC * 1000,
					 clk_get_rate(hw->clk));

		/* First compute the phase index (p), the remainder (r) is the
		 * part we'll try to acheive using the delays (d).
		 */
		r = do_div(p, 360 / phase_num);
		d = DIV_ROUND_CLOSEST(r * period_ps,
				      360 * mmc->delay_step_ps);
		d = min(d, mmc->delay_mask >> __ffs(mmc->delay_mask));
	}

	meson_mmc_apply_phase_delay(mmc, p, d);
	return 0;
}