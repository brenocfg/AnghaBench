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
typedef  size_t u32 ;
typedef  size_t u16 ;
struct aspeed_pwm_tacho_data {size_t clk_freq; size_t* type_pwm_clock_unit; size_t* type_pwm_clock_division_h; size_t* type_pwm_clock_division_l; size_t* type_fan_tach_unit; size_t* type_fan_tach_clock_division; } ;

/* Variables and functions */

__attribute__((used)) static u32 aspeed_get_fan_tach_ch_measure_period(struct aspeed_pwm_tacho_data
						 *priv, u8 type)
{
	u32 clk;
	u16 tacho_unit;
	u8 clk_unit, div_h, div_l, tacho_div;

	clk = priv->clk_freq;
	clk_unit = priv->type_pwm_clock_unit[type];
	div_h = priv->type_pwm_clock_division_h[type];
	div_h = 0x1 << div_h;
	div_l = priv->type_pwm_clock_division_l[type];
	if (div_l == 0)
		div_l = 1;
	else
		div_l = div_l * 2;

	tacho_unit = priv->type_fan_tach_unit[type];
	tacho_div = priv->type_fan_tach_clock_division[type];

	tacho_div = 0x4 << (tacho_div * 2);
	return clk / (clk_unit * div_h * div_l * tacho_div * tacho_unit);
}