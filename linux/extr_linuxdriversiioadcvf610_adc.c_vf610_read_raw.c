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
struct TYPE_2__ {int res_mode; size_t sample_rate; } ;
struct vf610_adc {int value; int vref_uv; int* sample_freq_avail; TYPE_1__ adc_feature; int /*<<< orphan*/  completion; scalar_t__ regs; } ;
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
#define  IIO_CHAN_INFO_PROCESSED 133 
#define  IIO_CHAN_INFO_RAW 132 
#define  IIO_CHAN_INFO_SAMP_FREQ 131 
#define  IIO_CHAN_INFO_SCALE 130 
#define  IIO_TEMP 129 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
#define  IIO_VOLTAGE 128 
 unsigned int VF610_ADC_ADCHC (int /*<<< orphan*/ ) ; 
 unsigned int VF610_ADC_AIEN ; 
 int /*<<< orphan*/  VF610_ADC_TIMEOUT ; 
 scalar_t__ VF610_REG_ADC_HC0 ; 
 int VF610_TEMP_SLOPE_COEFF ; 
 int /*<<< orphan*/  VF610_VTEMP25_3V3 ; 
 int /*<<< orphan*/  iio_buffer_enabled (struct iio_dev*) ; 
 struct vf610_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 long wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int vf610_read_raw(struct iio_dev *indio_dev,
			struct iio_chan_spec const *chan,
			int *val,
			int *val2,
			long mask)
{
	struct vf610_adc *info = iio_priv(indio_dev);
	unsigned int hc_cfg;
	long ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
	case IIO_CHAN_INFO_PROCESSED:
		mutex_lock(&indio_dev->mlock);
		if (iio_buffer_enabled(indio_dev)) {
			mutex_unlock(&indio_dev->mlock);
			return -EBUSY;
		}

		reinit_completion(&info->completion);
		hc_cfg = VF610_ADC_ADCHC(chan->channel);
		hc_cfg |= VF610_ADC_AIEN;
		writel(hc_cfg, info->regs + VF610_REG_ADC_HC0);
		ret = wait_for_completion_interruptible_timeout
				(&info->completion, VF610_ADC_TIMEOUT);
		if (ret == 0) {
			mutex_unlock(&indio_dev->mlock);
			return -ETIMEDOUT;
		}
		if (ret < 0) {
			mutex_unlock(&indio_dev->mlock);
			return ret;
		}

		switch (chan->type) {
		case IIO_VOLTAGE:
			*val = info->value;
			break;
		case IIO_TEMP:
			/*
			 * Calculate in degree Celsius times 1000
			 * Using the typical sensor slope of 1.84 mV/°C
			 * and VREFH_ADC at 3.3V, V at 25°C of 699 mV
			 */
			*val = 25000 - ((int)info->value - VF610_VTEMP25_3V3) *
					1000000 / VF610_TEMP_SLOPE_COEFF;

			break;
		default:
			mutex_unlock(&indio_dev->mlock);
			return -EINVAL;
		}

		mutex_unlock(&indio_dev->mlock);
		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SCALE:
		*val = info->vref_uv / 1000;
		*val2 = info->adc_feature.res_mode;
		return IIO_VAL_FRACTIONAL_LOG2;

	case IIO_CHAN_INFO_SAMP_FREQ:
		*val = info->sample_freq_avail[info->adc_feature.sample_rate];
		*val2 = 0;
		return IIO_VAL_INT;

	default:
		break;
	}

	return -EINVAL;
}