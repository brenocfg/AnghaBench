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
struct freq_tbl {int dummy; } ;
struct clk_rcg2 {int /*<<< orphan*/  freq_tbl; } ;
struct clk_hw {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __clk_is_enabled (int /*<<< orphan*/ ) ; 
 int __clk_rcg2_configure (struct clk_rcg2*,struct freq_tbl const*) ; 
 int clk_rcg2_shared_force_enable_clear (struct clk_hw*,struct freq_tbl const*) ; 
 struct freq_tbl* qcom_find_freq (int /*<<< orphan*/ ,unsigned long) ; 
 struct clk_rcg2* to_clk_rcg2 (struct clk_hw*) ; 

__attribute__((used)) static int clk_rcg2_shared_set_rate(struct clk_hw *hw, unsigned long rate,
				    unsigned long parent_rate)
{
	struct clk_rcg2 *rcg = to_clk_rcg2(hw);
	const struct freq_tbl *f;

	f = qcom_find_freq(rcg->freq_tbl, rate);
	if (!f)
		return -EINVAL;

	/*
	 * In case clock is disabled, update the CFG, M, N and D registers
	 * and don't hit the update bit of CMD register.
	 */
	if (!__clk_is_enabled(hw->clk))
		return __clk_rcg2_configure(rcg, f);

	return clk_rcg2_shared_force_enable_clear(hw, f);
}