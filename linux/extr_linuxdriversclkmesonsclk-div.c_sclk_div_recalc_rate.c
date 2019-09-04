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
typedef  int /*<<< orphan*/  u64 ;
struct meson_sclk_div_data {int /*<<< orphan*/  cached_div; } ;
struct clk_regmap {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP_ULL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct meson_sclk_div_data* meson_sclk_div_data (struct clk_regmap*) ; 
 struct clk_regmap* to_clk_regmap (struct clk_hw*) ; 

__attribute__((used)) static unsigned long sclk_div_recalc_rate(struct clk_hw *hw,
					  unsigned long prate)
{
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct meson_sclk_div_data *sclk = meson_sclk_div_data(clk);

	return DIV_ROUND_UP_ULL((u64)prate, sclk->cached_div);
}