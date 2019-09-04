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
typedef  int u8 ;
struct clk_i2s_mux {int bus_id; int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_SFR_I2SCLKSEL ; 
 int /*<<< orphan*/  BIT (int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct clk_i2s_mux* to_clk_i2s_mux (struct clk_hw*) ; 

__attribute__((used)) static int clk_i2s_mux_set_parent(struct clk_hw *hw, u8 index)
{
	struct clk_i2s_mux *mux = to_clk_i2s_mux(hw);

	return regmap_update_bits(mux->regmap, AT91_SFR_I2SCLKSEL,
				  BIT(mux->bus_id), index << mux->bus_id);
}