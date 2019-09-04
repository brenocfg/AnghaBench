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
struct ltr501_data {int /*<<< orphan*/  lock_ps; int /*<<< orphan*/  reg_ps_intr; int /*<<< orphan*/  lock_als; int /*<<< orphan*/  reg_als_intr; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int type; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_INTENSITY 129 
#define  IIO_PROXIMITY 128 
 struct ltr501_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_field_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ltr501_write_event_config(struct iio_dev *indio_dev,
				     const struct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_direction dir, int state)
{
	struct ltr501_data *data = iio_priv(indio_dev);
	int ret;

	/* only 1 and 0 are valid inputs */
	if (state != 1  && state != 0)
		return -EINVAL;

	switch (chan->type) {
	case IIO_INTENSITY:
		mutex_lock(&data->lock_als);
		ret = regmap_field_write(data->reg_als_intr, state);
		mutex_unlock(&data->lock_als);
		return ret;
	case IIO_PROXIMITY:
		mutex_lock(&data->lock_ps);
		ret = regmap_field_write(data->reg_ps_intr, state);
		mutex_unlock(&data->lock_ps);
		return ret;
	default:
		return -EINVAL;
	}

	return -EINVAL;
}