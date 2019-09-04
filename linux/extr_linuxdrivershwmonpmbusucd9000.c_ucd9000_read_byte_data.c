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
 int ENODATA ; 
 int ENXIO ; 
#define  PMBUS_FAN_CONFIG_12 129 
#define  PMBUS_FAN_CONFIG_34 128 
 int ucd9000_get_fan_config (struct i2c_client*,int) ; 

__attribute__((used)) static int ucd9000_read_byte_data(struct i2c_client *client, int page, int reg)
{
	int ret = 0;
	int fan_config;

	switch (reg) {
	case PMBUS_FAN_CONFIG_12:
		if (page > 0)
			return -ENXIO;

		ret = ucd9000_get_fan_config(client, 0);
		if (ret < 0)
			return ret;
		fan_config = ret << 4;
		ret = ucd9000_get_fan_config(client, 1);
		if (ret < 0)
			return ret;
		fan_config |= ret;
		ret = fan_config;
		break;
	case PMBUS_FAN_CONFIG_34:
		if (page > 0)
			return -ENXIO;

		ret = ucd9000_get_fan_config(client, 2);
		if (ret < 0)
			return ret;
		fan_config = ret << 4;
		ret = ucd9000_get_fan_config(client, 3);
		if (ret < 0)
			return ret;
		fan_config |= ret;
		ret = fan_config;
		break;
	default:
		ret = -ENODATA;
		break;
	}
	return ret;
}