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
struct tcs3472_data {int high_thresh; int low_thresh; size_t apers; int /*<<< orphan*/  lock; int /*<<< orphan*/  atime; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
 int IIO_EV_DIR_RISING ; 
#define  IIO_EV_INFO_PERIOD 129 
#define  IIO_EV_INFO_VALUE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 unsigned int USEC_PER_SEC ; 
 struct tcs3472_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int* tcs3472_intr_pers ; 

__attribute__((used)) static int tcs3472_read_event(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_direction dir, enum iio_event_info info, int *val,
	int *val2)
{
	struct tcs3472_data *data = iio_priv(indio_dev);
	int ret;
	unsigned int period;

	mutex_lock(&data->lock);

	switch (info) {
	case IIO_EV_INFO_VALUE:
		*val = (dir == IIO_EV_DIR_RISING) ?
			data->high_thresh : data->low_thresh;
		ret = IIO_VAL_INT;
		break;
	case IIO_EV_INFO_PERIOD:
		period = (256 - data->atime) * 2400 *
			tcs3472_intr_pers[data->apers];
		*val = period / USEC_PER_SEC;
		*val2 = period % USEC_PER_SEC;
		ret = IIO_VAL_INT_PLUS_MICRO;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	mutex_unlock(&data->lock);

	return ret;
}