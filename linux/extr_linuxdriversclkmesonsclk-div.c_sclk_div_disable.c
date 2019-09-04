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
struct meson_sclk_div_data {int /*<<< orphan*/  div; } ;
struct clk_regmap {int /*<<< orphan*/  map; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  meson_parm_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct meson_sclk_div_data* meson_sclk_div_data (struct clk_regmap*) ; 
 struct clk_regmap* to_clk_regmap (struct clk_hw*) ; 

__attribute__((used)) static void sclk_div_disable(struct clk_hw *hw)
{
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct meson_sclk_div_data *sclk = meson_sclk_div_data(clk);

	meson_parm_write(clk->map, &sclk->div, 0);
}