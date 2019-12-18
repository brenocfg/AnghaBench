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
typedef  int u32 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 int ENOTSUPP ; 
 int MAX31785_NR_PAGES ; 
#define  PMBUS_FAN_COMMAND_1 131 
#define  PMBUS_READ_FAN_SPEED_1 130 
#define  PMBUS_VIRT_PWM_1 129 
#define  PMBUS_VIRT_PWM_ENABLE_1 128 
 int max31785_get_pwm (struct i2c_client*,int) ; 
 int max31785_get_pwm_mode (struct i2c_client*,int) ; 
 int max31785_read_long_data (struct i2c_client*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int max31785_read_word_data(struct i2c_client *client, int page,
				   int reg)
{
	u32 val;
	int rv;

	switch (reg) {
	case PMBUS_READ_FAN_SPEED_1:
		if (page < MAX31785_NR_PAGES)
			return -ENODATA;

		rv = max31785_read_long_data(client, page - MAX31785_NR_PAGES,
					     reg, &val);
		if (rv < 0)
			return rv;

		rv = (val >> 16) & 0xffff;
		break;
	case PMBUS_FAN_COMMAND_1:
		/*
		 * PMBUS_FAN_COMMAND_x is probed to judge whether or not to
		 * expose fan control registers.
		 *
		 * Don't expose fan_target attribute for virtual pages.
		 */
		rv = (page >= MAX31785_NR_PAGES) ? -ENOTSUPP : -ENODATA;
		break;
	case PMBUS_VIRT_PWM_1:
		rv = max31785_get_pwm(client, page);
		break;
	case PMBUS_VIRT_PWM_ENABLE_1:
		rv = max31785_get_pwm_mode(client, page);
		break;
	default:
		rv = -ENODATA;
		break;
	}

	return rv;
}