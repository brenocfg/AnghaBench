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
struct iio_dev {int /*<<< orphan*/  mlock; int /*<<< orphan*/  dev; } ;
struct iio_chan_spec {int /*<<< orphan*/  address; } ;
struct axp288_adc_info {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP288_ADC_TS_CURRENT_ON ; 
 int /*<<< orphan*/  AXP288_ADC_TS_CURRENT_ON_ONDEMAND ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 128 
 int axp288_adc_read_channel (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axp288_adc_set_ts (struct axp288_adc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct axp288_adc_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int axp288_adc_read_raw(struct iio_dev *indio_dev,
			struct iio_chan_spec const *chan,
			int *val, int *val2, long mask)
{
	int ret;
	struct axp288_adc_info *info = iio_priv(indio_dev);

	mutex_lock(&indio_dev->mlock);
	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (axp288_adc_set_ts(info, AXP288_ADC_TS_CURRENT_ON_ONDEMAND,
					chan->address)) {
			dev_err(&indio_dev->dev, "GPADC mode\n");
			ret = -EINVAL;
			break;
		}
		ret = axp288_adc_read_channel(val, chan->address, info->regmap);
		if (axp288_adc_set_ts(info, AXP288_ADC_TS_CURRENT_ON,
						chan->address))
			dev_err(&indio_dev->dev, "TS pin restore\n");
		break;
	default:
		ret = -EINVAL;
	}
	mutex_unlock(&indio_dev->mlock);

	return ret;
}