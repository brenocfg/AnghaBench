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
struct stk3310_data {int /*<<< orphan*/  lock; TYPE_1__* client; int /*<<< orphan*/  reg_ps_gain; int /*<<< orphan*/  reg_als_gain; int /*<<< orphan*/  reg_ps_it; int /*<<< orphan*/  reg_als_it; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {scalar_t__ type; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_INT_TIME 129 
#define  IIO_CHAN_INFO_SCALE 128 
 scalar_t__ IIO_LIGHT ; 
 scalar_t__ IIO_PROXIMITY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct stk3310_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_field_write (int /*<<< orphan*/ ,int) ; 
 int stk3310_get_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stk3310_it_table ; 
 int /*<<< orphan*/  stk3310_scale_table ; 

__attribute__((used)) static int stk3310_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val, int val2, long mask)
{
	int ret;
	int index;
	struct stk3310_data *data = iio_priv(indio_dev);

	if (chan->type != IIO_LIGHT && chan->type != IIO_PROXIMITY)
		return -EINVAL;

	switch (mask) {
	case IIO_CHAN_INFO_INT_TIME:
		index = stk3310_get_index(stk3310_it_table,
					  ARRAY_SIZE(stk3310_it_table),
					  val, val2);
		if (index < 0)
			return -EINVAL;
		mutex_lock(&data->lock);
		if (chan->type == IIO_LIGHT)
			ret = regmap_field_write(data->reg_als_it, index);
		else
			ret = regmap_field_write(data->reg_ps_it, index);
		if (ret < 0)
			dev_err(&data->client->dev,
				"sensor configuration failed\n");
		mutex_unlock(&data->lock);
		return ret;

	case IIO_CHAN_INFO_SCALE:
		index = stk3310_get_index(stk3310_scale_table,
					  ARRAY_SIZE(stk3310_scale_table),
					  val, val2);
		if (index < 0)
			return -EINVAL;
		mutex_lock(&data->lock);
		if (chan->type == IIO_LIGHT)
			ret = regmap_field_write(data->reg_als_gain, index);
		else
			ret = regmap_field_write(data->reg_ps_gain, index);
		if (ret < 0)
			dev_err(&data->client->dev,
				"sensor configuration failed\n");
		mutex_unlock(&data->lock);
		return ret;
	}

	return -EINVAL;
}