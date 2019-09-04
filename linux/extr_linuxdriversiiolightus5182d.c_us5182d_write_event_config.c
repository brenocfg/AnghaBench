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
typedef  int /*<<< orphan*/  u16 ;
struct us5182d_data {int rising_en; int falling_en; int /*<<< orphan*/  lock; void* power_mode; int /*<<< orphan*/  default_continuous; int /*<<< orphan*/  px_low_th; int /*<<< orphan*/  px_high_th; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_EV_DIR_FALLING 129 
#define  IIO_EV_DIR_RISING 128 
 void* US5182D_CONTINUOUS ; 
 void* US5182D_ONESHOT ; 
 int /*<<< orphan*/  US5182D_PXH_TH_DISABLE ; 
 int /*<<< orphan*/  US5182D_PXL_TH_DISABLE ; 
 struct us5182d_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int us5182d_px_enable (struct us5182d_data*) ; 
 int us5182d_set_power_state (struct us5182d_data*,int) ; 
 int us5182d_setup_prox (struct iio_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int us5182d_write_event_config(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_direction dir, int state)
{
	struct us5182d_data *data = iio_priv(indio_dev);
	int ret;
	u16 new_th;

	mutex_lock(&data->lock);

	switch (dir) {
	case IIO_EV_DIR_RISING:
		if (data->rising_en == state) {
			mutex_unlock(&data->lock);
			return 0;
		}
		new_th = US5182D_PXH_TH_DISABLE;
		if (state) {
			data->power_mode = US5182D_CONTINUOUS;
			ret = us5182d_set_power_state(data, true);
			if (ret < 0)
				goto err;
			ret = us5182d_px_enable(data);
			if (ret < 0)
				goto err_poweroff;
			new_th = data->px_high_th;
		}
		ret = us5182d_setup_prox(indio_dev, dir, new_th);
		if (ret < 0)
			goto err_poweroff;
		data->rising_en = state;
		break;
	case IIO_EV_DIR_FALLING:
		if (data->falling_en == state) {
			mutex_unlock(&data->lock);
			return 0;
		}
		new_th =  US5182D_PXL_TH_DISABLE;
		if (state) {
			data->power_mode = US5182D_CONTINUOUS;
			ret = us5182d_set_power_state(data, true);
			if (ret < 0)
				goto err;
			ret = us5182d_px_enable(data);
			if (ret < 0)
				goto err_poweroff;
			new_th = data->px_low_th;
		}
		ret = us5182d_setup_prox(indio_dev, dir, new_th);
		if (ret < 0)
			goto err_poweroff;
		data->falling_en = state;
		break;
	default:
		ret = -EINVAL;
		goto err;
	}

	if (!state) {
		ret = us5182d_set_power_state(data, false);
		if (ret < 0)
			goto err;
	}

	if (!data->falling_en && !data->rising_en && !data->default_continuous)
		data->power_mode = US5182D_ONESHOT;

	mutex_unlock(&data->lock);
	return 0;

err_poweroff:
	if (state)
		us5182d_set_power_state(data, false);
err:
	mutex_unlock(&data->lock);
	return ret;
}