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
struct sun4i_dclk {int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int SUN4I_TCON0_DCLK_DIV_SHIFT ; 
 int SUN4I_TCON0_DCLK_DIV_WIDTH ; 
 int /*<<< orphan*/  SUN4I_TCON0_DCLK_REG ; 
 struct sun4i_dclk* hw_to_dclk (struct clk_hw*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static unsigned long sun4i_dclk_recalc_rate(struct clk_hw *hw,
					    unsigned long parent_rate)
{
	struct sun4i_dclk *dclk = hw_to_dclk(hw);
	u32 val;

	regmap_read(dclk->regmap, SUN4I_TCON0_DCLK_REG, &val);

	val >>= SUN4I_TCON0_DCLK_DIV_SHIFT;
	val &= (1 << SUN4I_TCON0_DCLK_DIV_WIDTH) - 1;

	if (!val)
		val = 1;

	return parent_rate / val;
}