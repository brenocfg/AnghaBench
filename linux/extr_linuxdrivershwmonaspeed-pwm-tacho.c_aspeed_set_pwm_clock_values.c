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
typedef  size_t u8 ;
typedef  size_t u32 ;
struct regmap {int dummy; } ;
struct TYPE_2__ {size_t h_value; size_t l_value; size_t unit_value; int /*<<< orphan*/  clk_ctrl_mask; int /*<<< orphan*/  clk_ctrl_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__* type_params ; 

__attribute__((used)) static void aspeed_set_pwm_clock_values(struct regmap *regmap, u8 type,
					u8 div_high, u8 div_low, u8 unit)
{
	u32 reg_value = ((div_high << type_params[type].h_value) |
			 (div_low << type_params[type].l_value) |
			 (unit << type_params[type].unit_value));

	regmap_update_bits(regmap, type_params[type].clk_ctrl_reg,
			   type_params[type].clk_ctrl_mask, reg_value);
}