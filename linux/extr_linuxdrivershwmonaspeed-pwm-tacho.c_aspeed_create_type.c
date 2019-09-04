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
struct aspeed_pwm_tacho_data {int /*<<< orphan*/  regmap; int /*<<< orphan*/ * type_fan_tach_mode; int /*<<< orphan*/ * type_fan_tach_unit; int /*<<< orphan*/ * type_fan_tach_clock_division; int /*<<< orphan*/ * type_pwm_clock_unit; int /*<<< orphan*/ * type_pwm_clock_division_l; int /*<<< orphan*/ * type_pwm_clock_division_h; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_PWM_DIV_H ; 
 int /*<<< orphan*/  M_PWM_DIV_L ; 
 int /*<<< orphan*/  M_PWM_PERIOD ; 
 int /*<<< orphan*/  M_TACH_CLK_DIV ; 
 int /*<<< orphan*/  M_TACH_MODE ; 
 int /*<<< orphan*/  M_TACH_UNIT ; 
 size_t TYPEM ; 
 int /*<<< orphan*/  aspeed_set_pwm_clock_values (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aspeed_set_tacho_type_enable (int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  aspeed_set_tacho_type_values (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aspeed_create_type(struct aspeed_pwm_tacho_data *priv)
{
	priv->type_pwm_clock_division_h[TYPEM] = M_PWM_DIV_H;
	priv->type_pwm_clock_division_l[TYPEM] = M_PWM_DIV_L;
	priv->type_pwm_clock_unit[TYPEM] = M_PWM_PERIOD;
	aspeed_set_pwm_clock_values(priv->regmap, TYPEM, M_PWM_DIV_H,
				    M_PWM_DIV_L, M_PWM_PERIOD);
	aspeed_set_tacho_type_enable(priv->regmap, TYPEM, true);
	priv->type_fan_tach_clock_division[TYPEM] = M_TACH_CLK_DIV;
	priv->type_fan_tach_unit[TYPEM] = M_TACH_UNIT;
	priv->type_fan_tach_mode[TYPEM] = M_TACH_MODE;
	aspeed_set_tacho_type_values(priv->regmap, TYPEM, M_TACH_MODE,
				     M_TACH_UNIT, M_TACH_CLK_DIV);
}