#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t address; } ;
struct ads1015_data {int* data_rate; int /*<<< orphan*/  lock; TYPE_2__* thresh_data; TYPE_1__* channel_data; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;
struct TYPE_4__ {int high_thresh; int low_thresh; unsigned int comp_queue; } ;
struct TYPE_3__ {int data_rate; } ;

/* Variables and functions */
 int EINVAL ; 
 int IIO_EV_DIR_RISING ; 
#define  IIO_EV_INFO_PERIOD 129 
#define  IIO_EV_INFO_VALUE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int USEC_PER_SEC ; 
 int* ads1015_comp_queue ; 
 struct ads1015_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ads1015_read_event(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_direction dir, enum iio_event_info info, int *val,
	int *val2)
{
	struct ads1015_data *data = iio_priv(indio_dev);
	int ret;
	unsigned int comp_queue;
	int period;
	int dr;

	mutex_lock(&data->lock);

	switch (info) {
	case IIO_EV_INFO_VALUE:
		*val = (dir == IIO_EV_DIR_RISING) ?
			data->thresh_data[chan->address].high_thresh :
			data->thresh_data[chan->address].low_thresh;
		ret = IIO_VAL_INT;
		break;
	case IIO_EV_INFO_PERIOD:
		dr = data->channel_data[chan->address].data_rate;
		comp_queue = data->thresh_data[chan->address].comp_queue;
		period = ads1015_comp_queue[comp_queue] *
			USEC_PER_SEC / data->data_rate[dr];

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