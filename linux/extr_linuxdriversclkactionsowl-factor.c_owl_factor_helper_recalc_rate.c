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
typedef  unsigned long long u32 ;
struct owl_factor_hw {unsigned long long shift; int fct_flags; int /*<<< orphan*/  reg; struct clk_factor_table* table; } ;
struct TYPE_2__ {int /*<<< orphan*/  clk; } ;
struct owl_clk_common {TYPE_1__ hw; int /*<<< orphan*/  regmap; } ;
struct clk_factor_table {int dummy; } ;

/* Variables and functions */
 int CLK_DIVIDER_ALLOW_ZERO ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __clk_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _get_table_div_mul (struct clk_factor_table const*,unsigned long long,unsigned long long*,unsigned long long*) ; 
 unsigned long long div_mask (struct owl_factor_hw const*) ; 
 int /*<<< orphan*/  do_div (unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long*) ; 

unsigned long owl_factor_helper_recalc_rate(struct owl_clk_common *common,
					 const struct owl_factor_hw *factor_hw,
					 unsigned long parent_rate)
{
	const struct clk_factor_table *clkt = factor_hw->table;
	unsigned long long int rate;
	u32 reg, val, mul, div;

	div = 0;
	mul = 0;

	regmap_read(common->regmap, factor_hw->reg, &reg);

	val = reg >> factor_hw->shift;
	val &= div_mask(factor_hw);

	_get_table_div_mul(clkt, val, &mul, &div);
	if (!div) {
		WARN(!(factor_hw->fct_flags & CLK_DIVIDER_ALLOW_ZERO),
			"%s: Zero divisor and CLK_DIVIDER_ALLOW_ZERO not set\n",
			__clk_get_name(common->hw.clk));
		return parent_rate;
	}

	rate = (unsigned long long int)parent_rate * mul;
	do_div(rate, div);

	return rate;
}