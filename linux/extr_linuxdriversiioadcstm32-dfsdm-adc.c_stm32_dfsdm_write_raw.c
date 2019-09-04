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
struct stm32_dfsdm_filter {int dummy; } ;
struct stm32_dfsdm_channel {int /*<<< orphan*/  src; } ;
struct stm32_dfsdm_adc {size_t fl_id; int oversamp; unsigned int spi_freq; int sample_freq; TYPE_1__* dfsdm; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct iio_chan_spec {size_t channel; } ;
struct TYPE_2__ {unsigned int spi_master_freq; struct stm32_dfsdm_channel* ch_list; struct stm32_dfsdm_filter* fl_list; } ;

/* Variables and functions */
#define  DFSDM_CHANNEL_SPI_CLOCK_INTERNAL 132 
#define  DFSDM_CHANNEL_SPI_CLOCK_INTERNAL_DIV2_FALLING 131 
#define  DFSDM_CHANNEL_SPI_CLOCK_INTERNAL_DIV2_RISING 130 
 int EINVAL ; 
#define  IIO_CHAN_INFO_OVERSAMPLING_RATIO 129 
#define  IIO_CHAN_INFO_SAMP_FREQ 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,unsigned int) ; 
 struct stm32_dfsdm_adc* iio_priv (struct iio_dev*) ; 
 int stm32_dfsdm_set_osrs (struct stm32_dfsdm_filter*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int stm32_dfsdm_write_raw(struct iio_dev *indio_dev,
				 struct iio_chan_spec const *chan,
				 int val, int val2, long mask)
{
	struct stm32_dfsdm_adc *adc = iio_priv(indio_dev);
	struct stm32_dfsdm_filter *fl = &adc->dfsdm->fl_list[adc->fl_id];
	struct stm32_dfsdm_channel *ch = &adc->dfsdm->ch_list[chan->channel];
	unsigned int spi_freq;
	int ret = -EINVAL;

	switch (mask) {
	case IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		ret = stm32_dfsdm_set_osrs(fl, 0, val);
		if (!ret)
			adc->oversamp = val;

		return ret;

	case IIO_CHAN_INFO_SAMP_FREQ:
		if (!val)
			return -EINVAL;

		switch (ch->src) {
		case DFSDM_CHANNEL_SPI_CLOCK_INTERNAL:
			spi_freq = adc->dfsdm->spi_master_freq;
			break;
		case DFSDM_CHANNEL_SPI_CLOCK_INTERNAL_DIV2_FALLING:
		case DFSDM_CHANNEL_SPI_CLOCK_INTERNAL_DIV2_RISING:
			spi_freq = adc->dfsdm->spi_master_freq / 2;
			break;
		default:
			spi_freq = adc->spi_freq;
		}

		if (spi_freq % val)
			dev_warn(&indio_dev->dev,
				 "Sampling rate not accurate (%d)\n",
				 spi_freq / (spi_freq / val));

		ret = stm32_dfsdm_set_osrs(fl, 0, (spi_freq / val));
		if (ret < 0) {
			dev_err(&indio_dev->dev,
				"Not able to find parameter that match!\n");
			return ret;
		}
		adc->sample_freq = val;

		return 0;
	}

	return -EINVAL;
}