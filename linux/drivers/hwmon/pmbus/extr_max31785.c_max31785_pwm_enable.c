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
typedef  int u16 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int PB_FAN_1_RPM ; 
 int max31785_scale_pwm (int) ; 
 int /*<<< orphan*/  percent ; 
 int pmbus_get_fan_rate_cached (struct i2c_client*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pmbus_update_fan (struct i2c_client*,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  rpm ; 

__attribute__((used)) static int max31785_pwm_enable(struct i2c_client *client, int page,
				    u16 word)
{
	int config = 0;
	int rate;

	switch (word) {
	case 0:
		rate = 0x7fff;
		break;
	case 1:
		rate = pmbus_get_fan_rate_cached(client, page, 0, percent);
		if (rate < 0)
			return rate;
		rate = max31785_scale_pwm(rate);
		break;
	case 2:
		config = PB_FAN_1_RPM;
		rate = pmbus_get_fan_rate_cached(client, page, 0, rpm);
		if (rate < 0)
			return rate;
		break;
	case 3:
		rate = 0xffff;
		break;
	default:
		return -EINVAL;
	}

	return pmbus_update_fan(client, page, 0, config, PB_FAN_1_RPM, rate);
}