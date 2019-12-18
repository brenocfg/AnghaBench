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
typedef  size_t u8 ;
struct aspeed_pwm_tacho_data {int* pwm_present; int /*<<< orphan*/ * pwm_port_fan_ctrl; int /*<<< orphan*/  regmap; int /*<<< orphan*/ * pwm_port_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_FAN_CTRL ; 
 int /*<<< orphan*/  TYPEM ; 
 int /*<<< orphan*/  aspeed_set_pwm_port_enable (int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  aspeed_set_pwm_port_fan_ctrl (struct aspeed_pwm_tacho_data*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aspeed_set_pwm_port_type (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aspeed_create_pwm_port(struct aspeed_pwm_tacho_data *priv,
				   u8 pwm_port)
{
	aspeed_set_pwm_port_enable(priv->regmap, pwm_port, true);
	priv->pwm_present[pwm_port] = true;

	priv->pwm_port_type[pwm_port] = TYPEM;
	aspeed_set_pwm_port_type(priv->regmap, pwm_port, TYPEM);

	priv->pwm_port_fan_ctrl[pwm_port] = INIT_FAN_CTRL;
	aspeed_set_pwm_port_fan_ctrl(priv, pwm_port, INIT_FAN_CTRL);
}