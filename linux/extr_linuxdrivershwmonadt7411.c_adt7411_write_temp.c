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
 int ADT7411_REG_TEMP_HIGH (int) ; 
 int ADT7411_REG_TEMP_LOW (int) ; 
 long DIV_ROUND_CLOSEST (long,int) ; 
 int EOPNOTSUPP ; 
 long clamp_val (long,int,int) ; 
 struct adt7411_data* dev_get_drvdata (struct device*) ; 
#define  hwmon_temp_max 129 
#define  hwmon_temp_min 128 
 int i2c_smbus_write_byte_data (struct i2c_client*,int,long) ; 

__attribute__((used)) static int adt7411_write_temp(struct device *dev, u32 attr, int channel,
			      long val)
{
	struct adt7411_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int reg;

	val = clamp_val(val, -128000, 127000);
	val = DIV_ROUND_CLOSEST(val, 1000);

	switch (attr) {
	case hwmon_temp_min:
		reg = ADT7411_REG_TEMP_LOW(channel);
		break;
	case hwmon_temp_max:
		reg = ADT7411_REG_TEMP_HIGH(channel);
		break;
	default:
		return -EOPNOTSUPP;
	}

	return i2c_smbus_write_byte_data(client, reg, val);
}