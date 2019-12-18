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
struct TYPE_3__ {int shift; int /*<<< orphan*/  realbits; } ;
struct iio_chan_spec {size_t address; TYPE_1__ scan_type; } ;
struct ads1015_data {size_t event_channel; int* data_rate; int /*<<< orphan*/  lock; TYPE_2__* channel_data; } ;
struct TYPE_4__ {int pga; int data_rate; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  ads1015_event_channel_enabled (struct ads1015_data*) ; 
 int* ads1015_fullscale_range ; 
 int ads1015_get_adc_result (struct ads1015_data*,size_t,int*) ; 
 int ads1015_set_power_state (struct ads1015_data*,int) ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct ads1015_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sign_extend32 (int,int) ; 

__attribute__((used)) static int ads1015_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan, int *val,
			    int *val2, long mask)
{
	int ret, idx;
	struct ads1015_data *data = iio_priv(indio_dev);

	mutex_lock(&data->lock);
	switch (mask) {
	case IIO_CHAN_INFO_RAW: {
		int shift = chan->scan_type.shift;

		ret = iio_device_claim_direct_mode(indio_dev);
		if (ret)
			break;

		if (ads1015_event_channel_enabled(data) &&
				data->event_channel != chan->address) {
			ret = -EBUSY;
			goto release_direct;
		}

		ret = ads1015_set_power_state(data, true);
		if (ret < 0)
			goto release_direct;

		ret = ads1015_get_adc_result(data, chan->address, val);
		if (ret < 0) {
			ads1015_set_power_state(data, false);
			goto release_direct;
		}

		*val = sign_extend32(*val >> shift, 15 - shift);

		ret = ads1015_set_power_state(data, false);
		if (ret < 0)
			goto release_direct;

		ret = IIO_VAL_INT;
release_direct:
		iio_device_release_direct_mode(indio_dev);
		break;
	}
	case IIO_CHAN_INFO_SCALE:
		idx = data->channel_data[chan->address].pga;
		*val = ads1015_fullscale_range[idx];
		*val2 = chan->scan_type.realbits - 1;
		ret = IIO_VAL_FRACTIONAL_LOG2;
		break;
	case IIO_CHAN_INFO_SAMP_FREQ:
		idx = data->channel_data[chan->address].data_rate;
		*val = data->data_rate[idx];
		ret = IIO_VAL_INT;
		break;
	default:
		ret = -EINVAL;
		break;
	}
	mutex_unlock(&data->lock);

	return ret;
}