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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;
struct bmp280_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OVERSAMPLING_RATIO 131 
#define  IIO_HUMIDITYRELATIVE 130 
#define  IIO_PRESSURE 129 
#define  IIO_TEMP 128 
 int bmp280_write_oversampling_ratio_humid (struct bmp280_data*,int) ; 
 int bmp280_write_oversampling_ratio_press (struct bmp280_data*,int) ; 
 int bmp280_write_oversampling_ratio_temp (struct bmp280_data*,int) ; 
 struct bmp280_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bmp280_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int val, int val2, long mask)
{
	int ret = 0;
	struct bmp280_data *data = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		pm_runtime_get_sync(data->dev);
		mutex_lock(&data->lock);
		switch (chan->type) {
		case IIO_HUMIDITYRELATIVE:
			ret = bmp280_write_oversampling_ratio_humid(data, val);
			break;
		case IIO_PRESSURE:
			ret = bmp280_write_oversampling_ratio_press(data, val);
			break;
		case IIO_TEMP:
			ret = bmp280_write_oversampling_ratio_temp(data, val);
			break;
		default:
			ret = -EINVAL;
			break;
		}
		mutex_unlock(&data->lock);
		pm_runtime_mark_last_busy(data->dev);
		pm_runtime_put_autosuspend(data->dev);
		break;
	default:
		return -EINVAL;
	}

	return ret;
}