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
struct owl_clk_common {int dummy; } ;
struct owl_pll {int /*<<< orphan*/  pll_hw; struct owl_clk_common common; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct owl_pll* hw_to_owl_pll (struct clk_hw*) ; 
 int /*<<< orphan*/  owl_pll_set (struct owl_clk_common const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int owl_pll_enable(struct clk_hw *hw)
{
	struct owl_pll *pll = hw_to_owl_pll(hw);
	const struct owl_clk_common *common = &pll->common;

	owl_pll_set(common, &pll->pll_hw, true);

	return 0;
}