#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iio_dev {int dummy; } ;
struct TYPE_4__ {int realbits; } ;
struct iio_chan_spec {size_t address; TYPE_1__ scan_type; } ;
struct ads1015_data {int* data_rate; int /*<<< orphan*/  lock; TYPE_3__* thresh_data; TYPE_2__* channel_data; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;
struct TYPE_6__ {int high_thresh; int low_thresh; int comp_queue; } ;
struct TYPE_5__ {int data_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int IIO_EV_DIR_RISING ; 
#define  IIO_EV_INFO_PERIOD 129 
#define  IIO_EV_INFO_VALUE 128 
 int USEC_PER_SEC ; 
 int* ads1015_comp_queue ; 
 struct ads1015_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ads1015_write_event(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_direction dir, enum iio_event_info info, int val,
	int val2)
{
	struct ads1015_data *data = iio_priv(indio_dev);
	int realbits = chan->scan_type.realbits;
	int ret = 0;
	long long period;
	int i;
	int dr;

	mutex_lock(&data->lock);

	switch (info) {
	case IIO_EV_INFO_VALUE:
		if (val >= 1 << (realbits - 1) || val < -1 << (realbits - 1)) {
			ret = -EINVAL;
			break;
		}
		if (dir == IIO_EV_DIR_RISING)
			data->thresh_data[chan->address].high_thresh = val;
		else
			data->thresh_data[chan->address].low_thresh = val;
		break;
	case IIO_EV_INFO_PERIOD:
		dr = data->channel_data[chan->address].data_rate;
		period = val * USEC_PER_SEC + val2;

		for (i = 0; i < ARRAY_SIZE(ads1015_comp_queue) - 1; i++) {
			if (period <= ads1015_comp_queue[i] *
					USEC_PER_SEC / data->data_rate[dr])
				break;
		}
		data->thresh_data[chan->address].comp_queue = i;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	mutex_unlock(&data->lock);

	return ret;
}