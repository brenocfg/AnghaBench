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
struct ms_ht_dev {int /*<<< orphan*/  client; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  MS_SENSORS_CONFIG_REG_WRITE ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ms_sensors_read_config_reg (int /*<<< orphan*/ ,int*) ; 

ssize_t ms_sensors_write_resolution(struct ms_ht_dev *dev_data,
				    u8 i)
{
	u8 config_reg;
	int ret;

	ret = ms_sensors_read_config_reg(dev_data->client, &config_reg);
	if (ret)
		return ret;

	config_reg &= 0x7E;
	config_reg |= ((i & 1) << 7) + ((i & 2) >> 1);

	return i2c_smbus_write_byte_data(dev_data->client,
					 MS_SENSORS_CONFIG_REG_WRITE,
					 config_reg);
}