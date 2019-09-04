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
typedef  int /*<<< orphan*/  u16 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  PB_FAN_1_RPM ; 
#define  PMBUS_VIRT_PWM_1 129 
#define  PMBUS_VIRT_PWM_ENABLE_1 128 
 int max31785_pwm_enable (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max31785_scale_pwm (int /*<<< orphan*/ ) ; 
 int pmbus_update_fan (struct i2c_client*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max31785_write_word_data(struct i2c_client *client, int page,
				    int reg, u16 word)
{
	switch (reg) {
	case PMBUS_VIRT_PWM_1:
		return pmbus_update_fan(client, page, 0, 0, PB_FAN_1_RPM,
					max31785_scale_pwm(word));
	case PMBUS_VIRT_PWM_ENABLE_1:
		return max31785_pwm_enable(client, page, word);
	default:
		break;
	}

	return -ENODATA;
}