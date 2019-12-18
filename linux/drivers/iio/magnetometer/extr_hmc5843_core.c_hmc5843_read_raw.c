#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  scan_index; } ;
struct hmc5843_data {TYPE_1__* variant; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int* regval_to_nanoscale; int** regval_to_samp_freq; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HMC5843_CONFIG_REG_A ; 
 int /*<<< orphan*/  HMC5843_CONFIG_REG_B ; 
 unsigned int HMC5843_RANGE_GAIN_OFFSET ; 
 unsigned int HMC5843_RATE_OFFSET ; 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int IIO_VAL_INT_PLUS_NANO ; 
 int hmc5843_read_measurement (struct hmc5843_data*,int /*<<< orphan*/ ,int*) ; 
 struct hmc5843_data* iio_priv (struct iio_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int hmc5843_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long mask)
{
	struct hmc5843_data *data = iio_priv(indio_dev);
	unsigned int rval;
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		return hmc5843_read_measurement(data, chan->scan_index, val);
	case IIO_CHAN_INFO_SCALE:
		ret = regmap_read(data->regmap, HMC5843_CONFIG_REG_B, &rval);
		if (ret < 0)
			return ret;
		rval >>= HMC5843_RANGE_GAIN_OFFSET;
		*val = 0;
		*val2 = data->variant->regval_to_nanoscale[rval];
		return IIO_VAL_INT_PLUS_NANO;
	case IIO_CHAN_INFO_SAMP_FREQ:
		ret = regmap_read(data->regmap, HMC5843_CONFIG_REG_A, &rval);
		if (ret < 0)
			return ret;
		rval >>= HMC5843_RATE_OFFSET;
		*val = data->variant->regval_to_samp_freq[rval][0];
		*val2 = data->variant->regval_to_samp_freq[rval][1];
		return IIO_VAL_INT_PLUS_MICRO;
	}
	return -EINVAL;
}