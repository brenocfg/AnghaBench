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
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct clk_rcg {int /*<<< orphan*/  ns_reg; TYPE_1__ clkr; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_rcg* to_clk_rcg (struct clk_hw*) ; 

__attribute__((used)) static void clk_rcg_lcc_disable(struct clk_hw *hw)
{
	struct clk_rcg *rcg = to_clk_rcg(hw);
	u32 gfm = BIT(10);

	/* Use XO */
	regmap_update_bits(rcg->clkr.regmap, rcg->ns_reg, gfm, 0);
}