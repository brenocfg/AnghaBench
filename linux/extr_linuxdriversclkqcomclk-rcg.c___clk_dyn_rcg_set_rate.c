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
struct clk_hw {int dummy; } ;
struct clk_dyn_rcg {int /*<<< orphan*/  freq_tbl; } ;

/* Variables and functions */
 int EINVAL ; 
 int configure_bank (struct clk_dyn_rcg*,struct freq_tbl const*) ; 
 struct freq_tbl* qcom_find_freq (int /*<<< orphan*/ ,unsigned long) ; 
 struct clk_dyn_rcg* to_clk_dyn_rcg (struct clk_hw*) ; 

__attribute__((used)) static int __clk_dyn_rcg_set_rate(struct clk_hw *hw, unsigned long rate)
{
	struct clk_dyn_rcg *rcg = to_clk_dyn_rcg(hw);
	const struct freq_tbl *f;

	f = qcom_find_freq(rcg->freq_tbl, rate);
	if (!f)
		return -EINVAL;

	return configure_bank(rcg, f);
}