#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct vcnl4000_data {int /*<<< orphan*/  vcnl4000_lock; TYPE_1__* client; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  VCNL4000_COMMAND ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte_data (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_i2c_block_data (TYPE_1__*,int,int,int*) ; 
 int i2c_smbus_write_byte_data (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vcnl4000_measure(struct vcnl4000_data *data, u8 req_mask,
				u8 rdy_mask, u8 data_reg, int *val)
{
	int tries = 20;
	__be16 buf;
	int ret;

	mutex_lock(&data->vcnl4000_lock);

	ret = i2c_smbus_write_byte_data(data->client, VCNL4000_COMMAND,
					req_mask);
	if (ret < 0)
		goto fail;

	/* wait for data to become ready */
	while (tries--) {
		ret = i2c_smbus_read_byte_data(data->client, VCNL4000_COMMAND);
		if (ret < 0)
			goto fail;
		if (ret & rdy_mask)
			break;
		msleep(20); /* measurement takes up to 100 ms */
	}

	if (tries < 0) {
		dev_err(&data->client->dev,
			"vcnl4000_measure() failed, data not ready\n");
		ret = -EIO;
		goto fail;
	}

	ret = i2c_smbus_read_i2c_block_data(data->client,
		data_reg, sizeof(buf), (u8 *) &buf);
	if (ret < 0)
		goto fail;

	mutex_unlock(&data->vcnl4000_lock);
	*val = be16_to_cpu(buf);

	return 0;

fail:
	mutex_unlock(&data->vcnl4000_lock);
	return ret;
}