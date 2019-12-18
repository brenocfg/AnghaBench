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
typedef  int u16 ;
struct vl53l0x_data {struct i2c_client* client; } ;
struct iio_chan_spec {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  VL_REG_RESULT_RANGE_STATUS ; 
 int VL_REG_RESULT_RANGE_STATUS_COMPLETE ; 
 int /*<<< orphan*/  VL_REG_SYSRANGE_START ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_i2c_block_data (struct i2c_client*,int /*<<< orphan*/ ,int,int*) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int vl53l0x_read_proximity(struct vl53l0x_data *data,
				  const struct iio_chan_spec *chan,
				  int *val)
{
	struct i2c_client *client = data->client;
	u16 tries = 20;
	u8 buffer[12];
	int ret;

	ret = i2c_smbus_write_byte_data(client, VL_REG_SYSRANGE_START, 1);
	if (ret < 0)
		return ret;

	do {
		ret = i2c_smbus_read_byte_data(client,
					       VL_REG_RESULT_RANGE_STATUS);
		if (ret < 0)
			return ret;

		if (ret & VL_REG_RESULT_RANGE_STATUS_COMPLETE)
			break;

		usleep_range(1000, 5000);
	} while (--tries);
	if (!tries)
		return -ETIMEDOUT;

	ret = i2c_smbus_read_i2c_block_data(client, VL_REG_RESULT_RANGE_STATUS,
					    12, buffer);
	if (ret < 0)
		return ret;
	else if (ret != 12)
		return -EREMOTEIO;

	/* Values should be between 30~1200 in millimeters. */
	*val = (buffer[10] << 8) + buffer[11];

	return 0;
}