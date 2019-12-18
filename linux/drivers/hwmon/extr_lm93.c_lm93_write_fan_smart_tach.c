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
struct lm93_data {int sf_tach_to_pwm; int sfc2; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM93_REG_SFC2 ; 
 int /*<<< orphan*/  LM93_REG_SF_TACH_TO_PWM ; 
 void* lm93_read_byte (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm93_write_byte (struct i2c_client*,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static void lm93_write_fan_smart_tach(struct i2c_client *client,
	struct lm93_data *data, int fan, long value)
{
	/* insert the new mapping and write it out */
	data->sf_tach_to_pwm = lm93_read_byte(client, LM93_REG_SF_TACH_TO_PWM);
	data->sf_tach_to_pwm &= ~(0x3 << fan * 2);
	data->sf_tach_to_pwm |= value << fan * 2;
	lm93_write_byte(client, LM93_REG_SF_TACH_TO_PWM, data->sf_tach_to_pwm);

	/* insert the enable bit and write it out */
	data->sfc2 = lm93_read_byte(client, LM93_REG_SFC2);
	if (value)
		data->sfc2 |= 1 << fan;
	else
		data->sfc2 &= ~(1 << fan);
	lm93_write_byte(client, LM93_REG_SFC2, data->sfc2);
}