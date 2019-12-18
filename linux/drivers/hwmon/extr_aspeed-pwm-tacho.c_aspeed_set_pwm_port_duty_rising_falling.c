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
struct TYPE_2__ {size_t duty_ctrl_rise_point; size_t duty_ctrl_fall_point; int /*<<< orphan*/  duty_ctrl_rise_fall_mask; int /*<<< orphan*/  duty_ctrl_reg; } ;

/* Variables and functions */
 TYPE_1__* pwm_port_params ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void aspeed_set_pwm_port_duty_rising_falling(struct regmap *regmap,
						    u8 pwm_port, u8 rising,
						    u8 falling)
{
	u32 reg_value = (rising <<
			 pwm_port_params[pwm_port].duty_ctrl_rise_point);
	reg_value |= (falling <<
		      pwm_port_params[pwm_port].duty_ctrl_fall_point);

	regmap_update_bits(regmap, pwm_port_params[pwm_port].duty_ctrl_reg,
			   pwm_port_params[pwm_port].duty_ctrl_rise_fall_mask,
			   reg_value);
}