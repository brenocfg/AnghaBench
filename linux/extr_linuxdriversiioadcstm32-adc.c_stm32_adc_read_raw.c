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
struct stm32_adc {TYPE_1__* common; } ;
struct iio_dev {int dummy; } ;
struct TYPE_4__ {int realbits; } ;
struct iio_chan_spec {TYPE_2__ scan_type; int /*<<< orphan*/  differential; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int vref_mv; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  IIO_VOLTAGE ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct stm32_adc* iio_priv (struct iio_dev*) ; 
 int stm32_adc_single_conv (struct iio_dev*,struct iio_chan_spec const*,int*) ; 

__attribute__((used)) static int stm32_adc_read_raw(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan,
			      int *val, int *val2, long mask)
{
	struct stm32_adc *adc = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		if (ret)
			return ret;
		if (chan->type == IIO_VOLTAGE)
			ret = stm32_adc_single_conv(indio_dev, chan, val);
		else
			ret = -EINVAL;
		iio_device_release_direct_mode(indio_dev);
		return ret;

	case IIO_CHAN_INFO_SCALE:
		if (chan->differential) {
			*val = adc->common->vref_mv * 2;
			*val2 = chan->scan_type.realbits;
		} else {
			*val = adc->common->vref_mv;
			*val2 = chan->scan_type.realbits;
		}
		return IIO_VAL_FRACTIONAL_LOG2;

	case IIO_CHAN_INFO_OFFSET:
		if (chan->differential)
			/* ADC_full_scale / 2 */
			*val = -((1 << chan->scan_type.realbits) / 2);
		else
			*val = 0;
		return IIO_VAL_INT;

	default:
		return -EINVAL;
	}
}