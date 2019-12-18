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
 int /*<<< orphan*/  GENMASK (int,int) ; 
 int /*<<< orphan*/  SUN4I_TCON0_IO_POL_REG ; 
 struct sun4i_dclk* hw_to_dclk (struct clk_hw*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sun4i_dclk_set_phase(struct clk_hw *hw, int degrees)
{
	struct sun4i_dclk *dclk = hw_to_dclk(hw);
	u32 val = degrees / 120;

	val <<= 28;

	regmap_update_bits(dclk->regmap, SUN4I_TCON0_IO_POL_REG,
			   GENMASK(29, 28),
			   val);

	return 0;
}