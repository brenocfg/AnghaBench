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
typedef  int u16 ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t channel; } ;
struct iadc_chip {int* offset; int* rsense; int /*<<< orphan*/  gain; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
 int IADC_REF_GAIN_MICRO_VOLTS ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int,int,int) ; 
 int iadc_do_conversion (struct iadc_chip*,size_t,int*) ; 
 struct iadc_chip* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iadc_read_raw(struct iio_dev *indio_dev,
			 struct iio_chan_spec const *chan,
			 int *val, int *val2, long mask)
{
	struct iadc_chip *iadc = iio_priv(indio_dev);
	s32 isense_ua, vsense_uv;
	u16 adc_raw, vsense_raw;
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&iadc->lock);
		ret = iadc_do_conversion(iadc, chan->channel, &adc_raw);
		mutex_unlock(&iadc->lock);
		if (ret < 0)
			return ret;

		vsense_raw = adc_raw - iadc->offset[chan->channel];

		vsense_uv = vsense_raw * IADC_REF_GAIN_MICRO_VOLTS;
		vsense_uv /= (s32)iadc->gain - iadc->offset[chan->channel];

		isense_ua = vsense_uv / iadc->rsense[chan->channel];

		dev_dbg(iadc->dev, "off %d gain %d adc %d %duV I %duA\n",
			iadc->offset[chan->channel], iadc->gain,
			adc_raw, vsense_uv, isense_ua);

		*val = isense_ua;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = 1000;
		return IIO_VAL_INT_PLUS_MICRO;
	}

	return -EINVAL;
}