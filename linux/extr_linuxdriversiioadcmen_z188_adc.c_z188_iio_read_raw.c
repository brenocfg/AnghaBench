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
typedef  int /*<<< orphan*/  u16 ;
struct z188_adc {int /*<<< orphan*/  base; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct iio_chan_spec {int channel; } ;

/* Variables and functions */
 int ADC_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADC_OVR (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EIO ; 
#define  IIO_CHAN_INFO_RAW 128 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 struct z188_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  readw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int z188_iio_read_raw(struct iio_dev *iio_dev,
			struct iio_chan_spec const *chan,
			int *val,
			int *val2,
			long info)
{
	struct z188_adc *adc = iio_priv(iio_dev);
	int ret;
	u16 tmp;

	switch (info) {
	case IIO_CHAN_INFO_RAW:
		tmp = readw(adc->base + chan->channel * 4);

		if (ADC_OVR(tmp)) {
			dev_info(&iio_dev->dev,
				"Oversampling error on ADC channel %d\n",
				chan->channel);
			return -EIO;
		}
		*val = ADC_DATA(tmp);
		ret = IIO_VAL_INT;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}