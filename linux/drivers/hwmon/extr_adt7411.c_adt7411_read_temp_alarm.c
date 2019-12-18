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
struct device {int dummy; } ;
struct adt7411_data {struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADT7411_REG_STAT_1 ; 
 int ADT7411_STAT_1_EXT_TEMP_FAULT ; 
 int ADT7411_STAT_1_EXT_TEMP_HIGH_AIN1 ; 
 int ADT7411_STAT_1_EXT_TEMP_LOW ; 
 int ADT7411_STAT_1_INT_TEMP_HIGH ; 
 int ADT7411_STAT_1_INT_TEMP_LOW ; 
 int EOPNOTSUPP ; 
 struct adt7411_data* dev_get_drvdata (struct device*) ; 
#define  hwmon_temp_fault 130 
#define  hwmon_temp_max_alarm 129 
#define  hwmon_temp_min_alarm 128 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adt7411_read_temp_alarm(struct device *dev, u32 attr, int channel,
				   long *val)
{
	struct adt7411_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int ret, bit;

	ret = i2c_smbus_read_byte_data(client, ADT7411_REG_STAT_1);
	if (ret < 0)
		return ret;

	switch (attr) {
	case hwmon_temp_min_alarm:
		bit = channel ? ADT7411_STAT_1_EXT_TEMP_LOW
			      : ADT7411_STAT_1_INT_TEMP_LOW;
		break;
	case hwmon_temp_max_alarm:
		bit = channel ? ADT7411_STAT_1_EXT_TEMP_HIGH_AIN1
			      : ADT7411_STAT_1_INT_TEMP_HIGH;
		break;
	case hwmon_temp_fault:
		bit = ADT7411_STAT_1_EXT_TEMP_FAULT;
		break;
	default:
		return -EOPNOTSUPP;
	}

	*val = !!(ret & bit);
	return 0;
}