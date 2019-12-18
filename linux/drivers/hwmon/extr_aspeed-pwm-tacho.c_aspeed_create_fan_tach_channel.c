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
struct aspeed_pwm_tacho_data {int* fan_tach_present; int* fan_tach_ch_source; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  aspeed_set_fan_tach_ch_enable (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  aspeed_set_fan_tach_ch_source (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void aspeed_create_fan_tach_channel(struct aspeed_pwm_tacho_data *priv,
					   u8 *fan_tach_ch,
					   int count,
					   u8 pwm_source)
{
	u8 val, index;

	for (val = 0; val < count; val++) {
		index = fan_tach_ch[val];
		aspeed_set_fan_tach_ch_enable(priv->regmap, index, true);
		priv->fan_tach_present[index] = true;
		priv->fan_tach_ch_source[index] = pwm_source;
		aspeed_set_fan_tach_ch_source(priv->regmap, index, pwm_source);
	}
}