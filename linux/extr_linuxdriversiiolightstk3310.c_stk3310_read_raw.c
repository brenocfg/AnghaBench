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
struct stk3310_data {int /*<<< orphan*/  reg_ps_gain; int /*<<< orphan*/  reg_als_gain; int /*<<< orphan*/  reg_ps_it; int /*<<< orphan*/  reg_als_it; int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; struct i2c_client* client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {scalar_t__ type; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_INT_TIME 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 scalar_t__ IIO_LIGHT ; 
 scalar_t__ IIO_PROXIMITY ; 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int /*<<< orphan*/  STK3310_REG_ALS_DATA_MSB ; 
 int /*<<< orphan*/  STK3310_REG_PS_DATA_MSB ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct stk3310_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int regmap_field_read (int /*<<< orphan*/ ,unsigned int*) ; 
 int** stk3310_it_table ; 
 int** stk3310_scale_table ; 

__attribute__((used)) static int stk3310_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long mask)
{
	u8 reg;
	__be16 buf;
	int ret;
	unsigned int index;
	struct stk3310_data *data = iio_priv(indio_dev);
	struct i2c_client *client = data->client;

	if (chan->type != IIO_LIGHT && chan->type != IIO_PROXIMITY)
		return -EINVAL;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (chan->type == IIO_LIGHT)
			reg = STK3310_REG_ALS_DATA_MSB;
		else
			reg = STK3310_REG_PS_DATA_MSB;

		mutex_lock(&data->lock);
		ret = regmap_bulk_read(data->regmap, reg, &buf, 2);
		if (ret < 0) {
			dev_err(&client->dev, "register read failed\n");
			mutex_unlock(&data->lock);
			return ret;
		}
		*val = be16_to_cpu(buf);
		mutex_unlock(&data->lock);
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_INT_TIME:
		if (chan->type == IIO_LIGHT)
			ret = regmap_field_read(data->reg_als_it, &index);
		else
			ret = regmap_field_read(data->reg_ps_it, &index);
		if (ret < 0)
			return ret;

		*val = stk3310_it_table[index][0];
		*val2 = stk3310_it_table[index][1];
		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_SCALE:
		if (chan->type == IIO_LIGHT)
			ret = regmap_field_read(data->reg_als_gain, &index);
		else
			ret = regmap_field_read(data->reg_ps_gain, &index);
		if (ret < 0)
			return ret;

		*val = stk3310_scale_table[index][0];
		*val2 = stk3310_scale_table[index][1];
		return IIO_VAL_INT_PLUS_MICRO;
	}

	return -EINVAL;
}