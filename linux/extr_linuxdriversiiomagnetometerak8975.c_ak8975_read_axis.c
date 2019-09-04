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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct iio_dev {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct ak_def {int /*<<< orphan*/  range; int /*<<< orphan*/ * data_regs; } ;
struct ak8975_data {int /*<<< orphan*/  lock; struct i2c_client* client; struct ak_def* def; } ;
typedef  int /*<<< orphan*/  rval ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int IIO_VAL_INT ; 
 int ak8975_start_read_axis (struct ak8975_data*,struct i2c_client const*) ; 
 int clamp_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_i2c_block_data_or_emulated (struct i2c_client const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct ak8975_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s16 ; 

__attribute__((used)) static int ak8975_read_axis(struct iio_dev *indio_dev, int index, int *val)
{
	struct ak8975_data *data = iio_priv(indio_dev);
	const struct i2c_client *client = data->client;
	const struct ak_def *def = data->def;
	__le16 rval;
	u16 buff;
	int ret;

	pm_runtime_get_sync(&data->client->dev);

	mutex_lock(&data->lock);

	ret = ak8975_start_read_axis(data, client);
	if (ret)
		goto exit;

	ret = i2c_smbus_read_i2c_block_data_or_emulated(
			client, def->data_regs[index],
			sizeof(rval), (u8*)&rval);
	if (ret < 0)
		goto exit;

	mutex_unlock(&data->lock);

	pm_runtime_mark_last_busy(&data->client->dev);
	pm_runtime_put_autosuspend(&data->client->dev);

	/* Swap bytes and convert to valid range. */
	buff = le16_to_cpu(rval);
	*val = clamp_t(s16, buff, -def->range, def->range);
	return IIO_VAL_INT;

exit:
	mutex_unlock(&data->lock);
	dev_err(&client->dev, "Error in reading axis\n");
	return ret;
}