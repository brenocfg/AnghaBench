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
struct palmas_gpadc {int /*<<< orphan*/  dev; } ;
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct iio_chan_spec {int channel; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_PROCESSED 129 
#define  IIO_CHAN_INFO_RAW 128 
 int IIO_VAL_INT ; 
 int PALMAS_ADC_CH_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct palmas_gpadc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int palmas_gpadc_get_calibrated_code (struct palmas_gpadc*,int,int) ; 
 int /*<<< orphan*/  palmas_gpadc_read_done (struct palmas_gpadc*,int) ; 
 int palmas_gpadc_read_prepare (struct palmas_gpadc*,int) ; 
 int palmas_gpadc_start_conversion (struct palmas_gpadc*,int) ; 

__attribute__((used)) static int palmas_gpadc_read_raw(struct iio_dev *indio_dev,
	struct iio_chan_spec const *chan, int *val, int *val2, long mask)
{
	struct  palmas_gpadc *adc = iio_priv(indio_dev);
	int adc_chan = chan->channel;
	int ret = 0;

	if (adc_chan > PALMAS_ADC_CH_MAX)
		return -EINVAL;

	mutex_lock(&indio_dev->mlock);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
	case IIO_CHAN_INFO_PROCESSED:
		ret = palmas_gpadc_read_prepare(adc, adc_chan);
		if (ret < 0)
			goto out;

		ret = palmas_gpadc_start_conversion(adc, adc_chan);
		if (ret < 0) {
			dev_err(adc->dev,
			"ADC start conversion failed\n");
			goto out;
		}

		if (mask == IIO_CHAN_INFO_PROCESSED)
			ret = palmas_gpadc_get_calibrated_code(
							adc, adc_chan, ret);

		*val = ret;

		ret = IIO_VAL_INT;
		goto out;
	}

	mutex_unlock(&indio_dev->mlock);
	return ret;

out:
	palmas_gpadc_read_done(adc, adc_chan);
	mutex_unlock(&indio_dev->mlock);

	return ret;
}