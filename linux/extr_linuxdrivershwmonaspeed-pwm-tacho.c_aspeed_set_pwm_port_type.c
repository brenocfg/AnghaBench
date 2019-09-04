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
typedef  int u8 ;
typedef  int u32 ;
struct regmap {int dummy; } ;
struct TYPE_2__ {int type_part1; int type_part2; int /*<<< orphan*/  type_mask; int /*<<< orphan*/  ctrl_reg; } ;

/* Variables and functions */
 TYPE_1__* pwm_port_params ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void aspeed_set_pwm_port_type(struct regmap *regmap,
				     u8 pwm_port, u8 type)
{
	u32 reg_value = (type & 0x1) << pwm_port_params[pwm_port].type_part1;

	reg_value |= (type & 0x2) << pwm_port_params[pwm_port].type_part2;

	regmap_update_bits(regmap, pwm_port_params[pwm_port].ctrl_reg,
			   pwm_port_params[pwm_port].type_mask, reg_value);
}