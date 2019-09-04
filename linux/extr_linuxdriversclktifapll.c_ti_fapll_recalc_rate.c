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
struct fapll_data {int /*<<< orphan*/  base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,int) ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 scalar_t__ ti_fapll_clock_is_bypass (struct fapll_data*) ; 
 struct fapll_data* to_fapll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long ti_fapll_recalc_rate(struct clk_hw *hw,
					  unsigned long parent_rate)
{
	struct fapll_data *fd = to_fapll(hw);
	u32 fapll_n, fapll_p, v;
	u64 rate;

	if (ti_fapll_clock_is_bypass(fd))
		return parent_rate;

	rate = parent_rate;

	/* PLL pre-divider is P and multiplier is N */
	v = readl_relaxed(fd->base);
	fapll_p = (v >> 8) & 0xff;
	if (fapll_p)
		do_div(rate, fapll_p);
	fapll_n = v >> 16;
	if (fapll_n)
		rate *= fapll_n;

	return rate;
}