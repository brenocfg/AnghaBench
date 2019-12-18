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
struct tiadc_device {int channels; int* channel_line; scalar_t__* step_avg; scalar_t__* open_delay; int* sample_delay; int* channel_step; TYPE_1__* mfd_tscadc; } ;
struct iio_dev {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_STEPCONFIG (int) ; 
 int /*<<< orphan*/  REG_STEPDELAY (int) ; 
 unsigned int STEPCONFIG_AVG (scalar_t__) ; 
 scalar_t__ STEPCONFIG_AVG_16 ; 
 unsigned int STEPCONFIG_FIFO1 ; 
 unsigned int STEPCONFIG_INM_ADCREFM ; 
 unsigned int STEPCONFIG_INP (int) ; 
 unsigned int STEPCONFIG_MODE_SWCNT ; 
 unsigned int STEPCONFIG_RFM_VREFN ; 
 unsigned int STEPCONFIG_RFP_VREFP ; 
 unsigned int STEPDELAY_OPEN (scalar_t__) ; 
 scalar_t__ STEPDELAY_OPEN_MASK ; 
 unsigned int STEPDELAY_SAMPLE (int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int,...) ; 
 scalar_t__ ffs (scalar_t__) ; 
 scalar_t__ iio_buffer_enabled (struct iio_dev*) ; 
 struct tiadc_device* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  tiadc_writel (struct tiadc_device*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void tiadc_step_config(struct iio_dev *indio_dev)
{
	struct tiadc_device *adc_dev = iio_priv(indio_dev);
	struct device *dev = adc_dev->mfd_tscadc->dev;
	unsigned int stepconfig;
	int i, steps = 0;

	/*
	 * There are 16 configurable steps and 8 analog input
	 * lines available which are shared between Touchscreen and ADC.
	 *
	 * Steps forwards i.e. from 0 towards 16 are used by ADC
	 * depending on number of input lines needed.
	 * Channel would represent which analog input
	 * needs to be given to ADC to digitalize data.
	 */


	for (i = 0; i < adc_dev->channels; i++) {
		int chan;

		chan = adc_dev->channel_line[i];

		if (adc_dev->step_avg[i] > STEPCONFIG_AVG_16) {
			dev_warn(dev, "chan %d step_avg truncating to %d\n",
				 chan, STEPCONFIG_AVG_16);
			adc_dev->step_avg[i] = STEPCONFIG_AVG_16;
		}

		if (adc_dev->step_avg[i])
			stepconfig =
			STEPCONFIG_AVG(ffs(adc_dev->step_avg[i]) - 1) |
			STEPCONFIG_FIFO1;
		else
			stepconfig = STEPCONFIG_FIFO1;

		if (iio_buffer_enabled(indio_dev))
			stepconfig |= STEPCONFIG_MODE_SWCNT;

		tiadc_writel(adc_dev, REG_STEPCONFIG(steps),
				stepconfig | STEPCONFIG_INP(chan) |
				STEPCONFIG_INM_ADCREFM |
				STEPCONFIG_RFP_VREFP |
				STEPCONFIG_RFM_VREFN);

		if (adc_dev->open_delay[i] > STEPDELAY_OPEN_MASK) {
			dev_warn(dev, "chan %d open delay truncating to 0x3FFFF\n",
				 chan);
			adc_dev->open_delay[i] = STEPDELAY_OPEN_MASK;
		}

		if (adc_dev->sample_delay[i] > 0xFF) {
			dev_warn(dev, "chan %d sample delay truncating to 0xFF\n",
				 chan);
			adc_dev->sample_delay[i] = 0xFF;
		}

		tiadc_writel(adc_dev, REG_STEPDELAY(steps),
				STEPDELAY_OPEN(adc_dev->open_delay[i]) |
				STEPDELAY_SAMPLE(adc_dev->sample_delay[i]));

		adc_dev->channel_step[i] = steps;
		steps++;
	}
}