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
struct i2c_client {int dummy; } ;
struct f75375_data {scalar_t__ kind; int /*<<< orphan*/ * pwm; } ;

/* Variables and functions */
 int /*<<< orphan*/  F75375_REG_FAN_EXP (int) ; 
 int /*<<< orphan*/  F75375_REG_FAN_PWM_DUTY (int) ; 
 int /*<<< orphan*/  f75375_write16 (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f75375_write8 (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ f75387 ; 
 struct f75375_data* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static void f75375_write_pwm(struct i2c_client *client, int nr)
{
	struct f75375_data *data = i2c_get_clientdata(client);
	if (data->kind == f75387)
		f75375_write16(client, F75375_REG_FAN_EXP(nr), data->pwm[nr]);
	else
		f75375_write8(client, F75375_REG_FAN_PWM_DUTY(nr),
			      data->pwm[nr]);
}