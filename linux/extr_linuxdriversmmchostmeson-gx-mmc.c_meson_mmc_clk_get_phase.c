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
typedef  unsigned long u32 ;
struct meson_mmc_phase {unsigned long phase_mask; int delay_mask; unsigned long delay_step_ps; int /*<<< orphan*/  reg; } ;
struct clk_hw {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ NSEC_PER_SEC ; 
 unsigned long __ffs (unsigned long) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int hweight_long (unsigned long) ; 
 unsigned long readl (int /*<<< orphan*/ ) ; 
 struct meson_mmc_phase* to_meson_mmc_phase (struct clk_hw*) ; 

__attribute__((used)) static int meson_mmc_clk_get_phase(struct clk_hw *hw)
{
	struct meson_mmc_phase *mmc = to_meson_mmc_phase(hw);
	unsigned int phase_num = 1 <<  hweight_long(mmc->phase_mask);
	unsigned long period_ps, p, d;
		int degrees;
	u32 val;

	val = readl(mmc->reg);
	p = (val & mmc->phase_mask) >> __ffs(mmc->phase_mask);
	degrees = p * 360 / phase_num;

	if (mmc->delay_mask) {
		period_ps = DIV_ROUND_UP((unsigned long)NSEC_PER_SEC * 1000,
					 clk_get_rate(hw->clk));
		d = (val & mmc->delay_mask) >> __ffs(mmc->delay_mask);
		degrees += d * mmc->delay_step_ps * 360 / period_ps;
		degrees %= 360;
	}

	return degrees;
}