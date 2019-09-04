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
struct clk_pll {int /*<<< orphan*/  id; int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int clk_pll_ready (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_pll* to_clk_pll (struct clk_hw*) ; 

__attribute__((used)) static int clk_pll_is_prepared(struct clk_hw *hw)
{
	struct clk_pll *pll = to_clk_pll(hw);

	return clk_pll_ready(pll->regmap, pll->id);
}