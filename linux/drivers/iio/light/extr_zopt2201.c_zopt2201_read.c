#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct zopt2201_data {size_t res; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {unsigned long us; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  ZOPT2201_MAIN_CTRL ; 
 int /*<<< orphan*/  ZOPT2201_MAIN_STATUS ; 
 int ZOPT2201_MAIN_STATUS_DRDY ; 
 int ZOPT2201_UVB_DATA ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_i2c_block_data (struct i2c_client*,int,int,int*) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (unsigned long,unsigned long) ; 
 int zopt2201_enable_mode (struct zopt2201_data*,int) ; 
 TYPE_1__* zopt2201_resolution ; 

__attribute__((used)) static int zopt2201_read(struct zopt2201_data *data, u8 reg)
{
	struct i2c_client *client = data->client;
	int tries = 10;
	u8 buf[3];
	int ret;

	mutex_lock(&data->lock);
	ret = zopt2201_enable_mode(data, reg == ZOPT2201_UVB_DATA);
	if (ret < 0)
		goto fail;

	while (tries--) {
		unsigned long t = zopt2201_resolution[data->res].us;

		if (t <= 20000)
			usleep_range(t, t + 1000);
		else
			msleep(t / 1000);
		ret = i2c_smbus_read_byte_data(client, ZOPT2201_MAIN_STATUS);
		if (ret < 0)
			goto fail;
		if (ret & ZOPT2201_MAIN_STATUS_DRDY)
			break;
	}

	if (tries < 0) {
		ret = -ETIMEDOUT;
		goto fail;
	}

	ret = i2c_smbus_read_i2c_block_data(client, reg, sizeof(buf), buf);
	if (ret < 0)
		goto fail;

	ret = i2c_smbus_write_byte_data(client, ZOPT2201_MAIN_CTRL, 0x00);
	if (ret < 0)
		goto fail;
	mutex_unlock(&data->lock);

	return (buf[2] << 16) | (buf[1] << 8) | buf[0];

fail:
	mutex_unlock(&data->lock);
	return ret;
}