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

/* Variables and functions */
 int /*<<< orphan*/  percent ; 
 int pmbus_get_fan_rate_device (struct i2c_client*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max31785_get_pwm(struct i2c_client *client, int page)
{
	int rv;

	rv = pmbus_get_fan_rate_device(client, page, 0, percent);
	if (rv < 0)
		return rv;
	else if (rv >= 0x8000)
		return 0;
	else if (rv >= 0x2711)
		return 0x2710;

	return rv;
}