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
typedef  int u32 ;
struct imx7d_adc {int channel; int value; int vref_uv; int /*<<< orphan*/  vref; int /*<<< orphan*/  completion; } ;
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct iio_chan_spec {int channel; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  IMX7D_ADC_TIMEOUT ; 
 struct imx7d_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  imx7d_adc_channel_set (struct imx7d_adc*) ; 
 int imx7d_adc_get_sample_rate (struct imx7d_adc*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 long wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx7d_adc_read_raw(struct iio_dev *indio_dev,
			struct iio_chan_spec const *chan,
			int *val,
			int *val2,
			long mask)
{
	struct imx7d_adc *info = iio_priv(indio_dev);

	u32 channel;
	long ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&indio_dev->mlock);
		reinit_completion(&info->completion);

		channel = chan->channel & 0x03;
		info->channel = channel;
		imx7d_adc_channel_set(info);

		ret = wait_for_completion_interruptible_timeout
				(&info->completion, IMX7D_ADC_TIMEOUT);
		if (ret == 0) {
			mutex_unlock(&indio_dev->mlock);
			return -ETIMEDOUT;
		}
		if (ret < 0) {
			mutex_unlock(&indio_dev->mlock);
			return ret;
		}

		*val = info->value;
		mutex_unlock(&indio_dev->mlock);
		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SCALE:
		info->vref_uv = regulator_get_voltage(info->vref);
		*val = info->vref_uv / 1000;
		*val2 = 12;
		return IIO_VAL_FRACTIONAL_LOG2;

	case IIO_CHAN_INFO_SAMP_FREQ:
		*val = imx7d_adc_get_sample_rate(info);
		return IIO_VAL_INT;

	default:
		return -EINVAL;
	}
}