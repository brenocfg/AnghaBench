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
struct ltr501_data {int /*<<< orphan*/  lock_ps; int /*<<< orphan*/  regmap; int /*<<< orphan*/  lock_als; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int type; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_EV_DIR_FALLING 131 
#define  IIO_EV_DIR_RISING 130 
#define  IIO_INTENSITY 129 
#define  IIO_PROXIMITY 128 
 int /*<<< orphan*/  LTR501_ALS_THRESH_LOW ; 
 int LTR501_ALS_THRESH_MASK ; 
 int /*<<< orphan*/  LTR501_ALS_THRESH_UP ; 
 int /*<<< orphan*/  LTR501_PS_THRESH_LOW ; 
 int LTR501_PS_THRESH_MASK ; 
 int /*<<< orphan*/  LTR501_PS_THRESH_UP ; 
 struct ltr501_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int ltr501_write_thresh(struct iio_dev *indio_dev,
			       const struct iio_chan_spec *chan,
			       enum iio_event_type type,
			       enum iio_event_direction dir,
			       enum iio_event_info info,
			       int val, int val2)
{
	struct ltr501_data *data = iio_priv(indio_dev);
	int ret;

	if (val < 0)
		return -EINVAL;

	switch (chan->type) {
	case IIO_INTENSITY:
		if (val > LTR501_ALS_THRESH_MASK)
			return -EINVAL;
		switch (dir) {
		case IIO_EV_DIR_RISING:
			mutex_lock(&data->lock_als);
			ret = regmap_bulk_write(data->regmap,
						LTR501_ALS_THRESH_UP,
						&val, 2);
			mutex_unlock(&data->lock_als);
			return ret;
		case IIO_EV_DIR_FALLING:
			mutex_lock(&data->lock_als);
			ret = regmap_bulk_write(data->regmap,
						LTR501_ALS_THRESH_LOW,
						&val, 2);
			mutex_unlock(&data->lock_als);
			return ret;
		default:
			return -EINVAL;
		}
	case IIO_PROXIMITY:
		if (val > LTR501_PS_THRESH_MASK)
			return -EINVAL;
		switch (dir) {
		case IIO_EV_DIR_RISING:
			mutex_lock(&data->lock_ps);
			ret = regmap_bulk_write(data->regmap,
						LTR501_PS_THRESH_UP,
						&val, 2);
			mutex_unlock(&data->lock_ps);
			return ret;
		case IIO_EV_DIR_FALLING:
			mutex_lock(&data->lock_ps);
			ret = regmap_bulk_write(data->regmap,
						LTR501_PS_THRESH_LOW,
						&val, 2);
			mutex_unlock(&data->lock_ps);
			return ret;
		default:
			return -EINVAL;
		}
	default:
		return -EINVAL;
	}

	return -EINVAL;
}