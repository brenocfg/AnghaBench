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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;
struct bmp280_data {int oversampling_humid; int oversampling_press; int oversampling_temp; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; TYPE_1__* chip_info; } ;
struct TYPE_2__ {int (* read_humid ) (struct bmp280_data*,int*,int*) ;int (* read_press ) (struct bmp280_data*,int*,int*) ;int (* read_temp ) (struct bmp280_data*,int*) ;} ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OVERSAMPLING_RATIO 132 
#define  IIO_CHAN_INFO_PROCESSED 131 
#define  IIO_HUMIDITYRELATIVE 130 
#define  IIO_PRESSURE 129 
#define  IIO_TEMP 128 
 int IIO_VAL_INT ; 
 struct bmp280_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int stub1 (struct bmp280_data*,int*,int*) ; 
 int stub2 (struct bmp280_data*,int*,int*) ; 
 int stub3 (struct bmp280_data*,int*) ; 

__attribute__((used)) static int bmp280_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val, int *val2, long mask)
{
	int ret;
	struct bmp280_data *data = iio_priv(indio_dev);

	pm_runtime_get_sync(data->dev);
	mutex_lock(&data->lock);

	switch (mask) {
	case IIO_CHAN_INFO_PROCESSED:
		switch (chan->type) {
		case IIO_HUMIDITYRELATIVE:
			ret = data->chip_info->read_humid(data, val, val2);
			break;
		case IIO_PRESSURE:
			ret = data->chip_info->read_press(data, val, val2);
			break;
		case IIO_TEMP:
			ret = data->chip_info->read_temp(data, val);
			break;
		default:
			ret = -EINVAL;
			break;
		}
		break;
	case IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		switch (chan->type) {
		case IIO_HUMIDITYRELATIVE:
			*val = 1 << data->oversampling_humid;
			ret = IIO_VAL_INT;
			break;
		case IIO_PRESSURE:
			*val = 1 << data->oversampling_press;
			ret = IIO_VAL_INT;
			break;
		case IIO_TEMP:
			*val = 1 << data->oversampling_temp;
			ret = IIO_VAL_INT;
			break;
		default:
			ret = -EINVAL;
			break;
		}
		break;
	default:
		ret = -EINVAL;
		break;
	}

	mutex_unlock(&data->lock);
	pm_runtime_mark_last_busy(data->dev);
	pm_runtime_put_autosuspend(data->dev);

	return ret;
}