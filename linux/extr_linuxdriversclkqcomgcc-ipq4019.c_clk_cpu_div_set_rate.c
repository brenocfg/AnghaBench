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
typedef  int u32 ;
struct freq_tbl {int pre_div; } ;
struct clk_hw {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  regmap; } ;
struct TYPE_4__ {int shift; int /*<<< orphan*/  reg; TYPE_1__ clkr; int /*<<< orphan*/  width; } ;
struct clk_fepll {TYPE_2__ cdiv; int /*<<< orphan*/  freq_tbl; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 struct freq_tbl* qcom_find_freq (int /*<<< orphan*/ ,unsigned long) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct clk_fepll* to_clk_fepll (struct clk_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int clk_cpu_div_set_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long parent_rate)
{
	struct clk_fepll *pll = to_clk_fepll(hw);
	const struct freq_tbl *f;
	u32 mask;
	int ret;

	f = qcom_find_freq(pll->freq_tbl, rate);
	if (!f)
		return -EINVAL;

	mask = (BIT(pll->cdiv.width) - 1) << pll->cdiv.shift;
	ret = regmap_update_bits(pll->cdiv.clkr.regmap,
				 pll->cdiv.reg, mask,
				 f->pre_div << pll->cdiv.shift);
	/*
	 * There is no status bit which can be checked for successful CPU
	 * divider update operation so using delay for the same.
	 */
	udelay(1);

	return 0;
}