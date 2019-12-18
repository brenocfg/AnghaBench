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
struct us5182d_data {int px_high_th; int px_low_th; int /*<<< orphan*/  lock; int /*<<< orphan*/  falling_en; int /*<<< orphan*/  rising_en; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_EV_DIR_FALLING 129 
#define  IIO_EV_DIR_RISING 128 
 int USHRT_MAX ; 
 struct us5182d_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int us5182d_setup_prox (struct iio_dev*,int,int) ; 

__attribute__((used)) static int us5182d_write_thresh(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_direction dir, enum iio_event_info info, int val,
	int val2)
{
	struct us5182d_data *data = iio_priv(indio_dev);
	int ret;

	if (val < 0 || val > USHRT_MAX || val2 != 0)
		return -EINVAL;

	switch (dir) {
	case IIO_EV_DIR_RISING:
		mutex_lock(&data->lock);
		if (data->rising_en) {
			ret = us5182d_setup_prox(indio_dev, dir, val);
			if (ret < 0)
				goto err;
		}
		data->px_high_th = val;
		mutex_unlock(&data->lock);
		break;
	case IIO_EV_DIR_FALLING:
		mutex_lock(&data->lock);
		if (data->falling_en) {
			ret = us5182d_setup_prox(indio_dev, dir, val);
			if (ret < 0)
				goto err;
		}
		data->px_low_th = val;
		mutex_unlock(&data->lock);
		break;
	default:
		return -EINVAL;
	}

	return 0;
err:
	mutex_unlock(&data->lock);
	return ret;
}