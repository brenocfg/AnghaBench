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
typedef  unsigned int u16 ;
struct iio_dev {int dummy; } ;
struct cc10001_adc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC10001_ADC_CHSEL_SAMPLED ; 
 unsigned int CC10001_ADC_CH_MASK ; 
 unsigned int CC10001_ADC_DATA_MASK ; 
 int /*<<< orphan*/  CC10001_ADC_DDATA_OUT ; 
 int /*<<< orphan*/  CC10001_ADC_EOC ; 
 unsigned int CC10001_ADC_EOC_SET ; 
 unsigned int CC10001_INVALID_SAMPLED ; 
 int /*<<< orphan*/  CC10001_MAX_POLL_COUNT ; 
 unsigned int cc10001_adc_read_reg (struct cc10001_adc_device*,int /*<<< orphan*/ ) ; 
 struct cc10001_adc_device* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  ndelay (unsigned int) ; 

__attribute__((used)) static u16 cc10001_adc_poll_done(struct iio_dev *indio_dev,
				 unsigned int channel,
				 unsigned int delay)
{
	struct cc10001_adc_device *adc_dev = iio_priv(indio_dev);
	unsigned int poll_count = 0;

	while (!(cc10001_adc_read_reg(adc_dev, CC10001_ADC_EOC) &
			CC10001_ADC_EOC_SET)) {

		ndelay(delay);
		if (poll_count++ == CC10001_MAX_POLL_COUNT)
			return CC10001_INVALID_SAMPLED;
	}

	poll_count = 0;
	while ((cc10001_adc_read_reg(adc_dev, CC10001_ADC_CHSEL_SAMPLED) &
			CC10001_ADC_CH_MASK) != channel) {

		ndelay(delay);
		if (poll_count++ == CC10001_MAX_POLL_COUNT)
			return CC10001_INVALID_SAMPLED;
	}

	/* Read the 10 bit output register */
	return cc10001_adc_read_reg(adc_dev, CC10001_ADC_DDATA_OUT) &
			       CC10001_ADC_DATA_MASK;
}