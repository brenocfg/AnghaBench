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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
struct adxl372_state {int bw; int /*<<< orphan*/  inact_time_ms; int /*<<< orphan*/  act_time_ms; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY 129 
#define  IIO_CHAN_INFO_SAMP_FREQ 128 
 int /*<<< orphan*/  adxl372_bw_freq_tbl ; 
 int adxl372_find_closest_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  adxl372_samp_freq_tbl ; 
 int adxl372_set_activity_time_ms (struct adxl372_state*,int /*<<< orphan*/ ) ; 
 int adxl372_set_bandwidth (struct adxl372_state*,int) ; 
 int adxl372_set_inactivity_time_ms (struct adxl372_state*,int /*<<< orphan*/ ) ; 
 int adxl372_set_odr (struct adxl372_state*,int) ; 
 struct adxl372_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int adxl372_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val, int val2, long info)
{
	struct adxl372_state *st = iio_priv(indio_dev);
	int odr_index, bw_index, ret;

	switch (info) {
	case IIO_CHAN_INFO_SAMP_FREQ:
		odr_index = adxl372_find_closest_match(adxl372_samp_freq_tbl,
					ARRAY_SIZE(adxl372_samp_freq_tbl),
					val);
		ret = adxl372_set_odr(st, odr_index);
		if (ret < 0)
			return ret;
		/*
		 * The timer period depends on the ODR selected.
		 * At 3200 Hz and below, it is 6.6 ms; at 6400 Hz, it is 3.3 ms
		 */
		ret = adxl372_set_activity_time_ms(st, st->act_time_ms);
		if (ret < 0)
			return ret;
		/*
		 * The timer period depends on the ODR selected.
		 * At 3200 Hz and below, it is 26 ms; at 6400 Hz, it is 13 ms
		 */
		ret = adxl372_set_inactivity_time_ms(st, st->inact_time_ms);
		if (ret < 0)
			return ret;
		/*
		 * The maximum bandwidth is constrained to at most half of
		 * the ODR to ensure that the Nyquist criteria is not violated
		 */
		if (st->bw > odr_index)
			ret = adxl372_set_bandwidth(st, odr_index);

		return ret;
	case IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		bw_index = adxl372_find_closest_match(adxl372_bw_freq_tbl,
					ARRAY_SIZE(adxl372_bw_freq_tbl),
					val);
		return adxl372_set_bandwidth(st, bw_index);
	default:
		return -EINVAL;
	}
}