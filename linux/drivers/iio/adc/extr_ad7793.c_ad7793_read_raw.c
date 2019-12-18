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
struct TYPE_3__ {int /*<<< orphan*/  realbits; } ;
struct iio_chan_spec {int const type; TYPE_1__ scan_type; int /*<<< orphan*/  differential; } ;
struct ad7793_state {int conf; int** scale_avail; int /*<<< orphan*/  mode; TYPE_2__* chip_info; } ;
struct TYPE_4__ {int* sample_freq_avail; } ;

/* Variables and functions */
 int AD7793_CONF_UNIPOLAR ; 
 size_t AD7793_MODE_RATE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 133 
#define  IIO_CHAN_INFO_RAW 132 
#define  IIO_CHAN_INFO_SAMP_FREQ 131 
#define  IIO_CHAN_INFO_SCALE 130 
#define  IIO_TEMP 129 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_NANO ; 
#define  IIO_VOLTAGE 128 
 int ad_sigma_delta_single_conversion (struct iio_dev*,struct iio_chan_spec const*,int*) ; 
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 
 struct ad7793_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad7793_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val,
			   int *val2,
			   long m)
{
	struct ad7793_state *st = iio_priv(indio_dev);
	int ret;
	unsigned long long scale_uv;
	bool unipolar = !!(st->conf & AD7793_CONF_UNIPOLAR);

	switch (m) {
	case IIO_CHAN_INFO_RAW:
		ret = ad_sigma_delta_single_conversion(indio_dev, chan, val);
		if (ret < 0)
			return ret;

		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_VOLTAGE:
			if (chan->differential) {
				*val = st->
					scale_avail[(st->conf >> 8) & 0x7][0];
				*val2 = st->
					scale_avail[(st->conf >> 8) & 0x7][1];
				return IIO_VAL_INT_PLUS_NANO;
			}
			/* 1170mV / 2^23 * 6 */
			scale_uv = (1170ULL * 1000000000ULL * 6ULL);
			break;
		case IIO_TEMP:
				/* 1170mV / 0.81 mV/C / 2^23 */
				scale_uv = 1444444444444444ULL;
			break;
		default:
			return -EINVAL;
		}

		scale_uv >>= (chan->scan_type.realbits - (unipolar ? 0 : 1));
		*val = 0;
		*val2 = scale_uv;
		return IIO_VAL_INT_PLUS_NANO;
	case IIO_CHAN_INFO_OFFSET:
		if (!unipolar)
			*val = -(1 << (chan->scan_type.realbits - 1));
		else
			*val = 0;

		/* Kelvin to Celsius */
		if (chan->type == IIO_TEMP) {
			unsigned long long offset;
			unsigned int shift;

			shift = chan->scan_type.realbits - (unipolar ? 0 : 1);
			offset = 273ULL << shift;
			do_div(offset, 1444);
			*val -= offset;
		}
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SAMP_FREQ:
		*val = st->chip_info
			       ->sample_freq_avail[AD7793_MODE_RATE(st->mode)];
		return IIO_VAL_INT;
	}
	return -EINVAL;
}