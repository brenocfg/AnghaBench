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
typedef  int u32 ;
struct clk_hw {int dummy; } ;
struct axxia_divclk {int shift; int width; int /*<<< orphan*/  reg; } ;
struct axxia_clk {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct axxia_clk* to_axxia_clk (struct clk_hw*) ; 
 struct axxia_divclk* to_axxia_divclk (struct axxia_clk*) ; 

__attribute__((used)) static unsigned long
axxia_divclk_recalc_rate(struct clk_hw *hw, unsigned long parent_rate)
{
	struct axxia_clk *aclk = to_axxia_clk(hw);
	struct axxia_divclk *divclk = to_axxia_divclk(aclk);
	u32 ctrl, div;

	regmap_read(aclk->regmap, divclk->reg, &ctrl);
	div = 1 + ((ctrl >> divclk->shift) & ((1 << divclk->width)-1));

	return parent_rate / div;
}