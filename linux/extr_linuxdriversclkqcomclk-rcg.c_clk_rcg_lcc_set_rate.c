#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct freq_tbl {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct clk_rcg {int /*<<< orphan*/  ns_reg; TYPE_1__ clkr; int /*<<< orphan*/  freq_tbl; } ;
struct clk_hw {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int EINVAL ; 
 scalar_t__ __clk_is_enabled (int /*<<< orphan*/ ) ; 
 int __clk_rcg_set_rate (struct clk_rcg*,struct freq_tbl const*) ; 
 struct freq_tbl* qcom_find_freq (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_rcg* to_clk_rcg (struct clk_hw*) ; 

__attribute__((used)) static int clk_rcg_lcc_set_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long parent_rate)
{
	struct clk_rcg *rcg = to_clk_rcg(hw);
	const struct freq_tbl *f;
	int ret;
	u32 gfm = BIT(10);

	f = qcom_find_freq(rcg->freq_tbl, rate);
	if (!f)
		return -EINVAL;

	/* Switch to XO to avoid glitches */
	regmap_update_bits(rcg->clkr.regmap, rcg->ns_reg, gfm, 0);
	ret = __clk_rcg_set_rate(rcg, f);
	/* Switch back to M/N if it's clocking */
	if (__clk_is_enabled(hw->clk))
		regmap_update_bits(rcg->clkr.regmap, rcg->ns_reg, gfm, gfm);

	return ret;
}