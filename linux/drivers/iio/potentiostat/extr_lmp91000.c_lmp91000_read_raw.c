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
struct lmp91000_data {int /*<<< orphan*/  adc_chan; int /*<<< orphan*/  cb_buffer; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 131 
#define  IIO_CHAN_INFO_PROCESSED 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  LMP91000_TEMP_BASE ; 
 int iio_channel_start_all_cb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_channel_stop_all_cb (int /*<<< orphan*/ ) ; 
 int iio_convert_raw_to_processed (int /*<<< orphan*/ ,int,int*,int) ; 
 struct lmp91000_data* iio_priv (struct iio_dev*) ; 
 int iio_read_channel_offset (int /*<<< orphan*/ ,int*,int*) ; 
 int iio_read_channel_scale (int /*<<< orphan*/ ,int*,int*) ; 
 int lmp91000_read (struct lmp91000_data*,int /*<<< orphan*/ ,int*) ; 
 int* lmp91000_temp_lut ; 

__attribute__((used)) static int lmp91000_read_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int *val, int *val2, long mask)
{
	struct lmp91000_data *data = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
	case IIO_CHAN_INFO_PROCESSED: {
		int ret = iio_channel_start_all_cb(data->cb_buffer);

		if (ret)
			return ret;

		ret = lmp91000_read(data, chan->address, val);

		iio_channel_stop_all_cb(data->cb_buffer);

		if (ret)
			return ret;

		if (mask == IIO_CHAN_INFO_PROCESSED) {
			int tmp, i;

			ret = iio_convert_raw_to_processed(data->adc_chan,
							   *val, &tmp, 1);
			if (ret)
				return ret;

			for (i = 0; i < ARRAY_SIZE(lmp91000_temp_lut); i++)
				if (lmp91000_temp_lut[i] < tmp)
					break;

			*val = (LMP91000_TEMP_BASE + i) * 1000;
		}
		return IIO_VAL_INT;
	}
	case IIO_CHAN_INFO_OFFSET:
		return iio_read_channel_offset(data->adc_chan, val, val2);
	case IIO_CHAN_INFO_SCALE:
		return iio_read_channel_scale(data->adc_chan, val, val2);
	}

	return -EINVAL;
}