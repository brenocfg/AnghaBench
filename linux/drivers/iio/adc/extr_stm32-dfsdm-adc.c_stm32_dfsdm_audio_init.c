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
struct stm32_dfsdm_channel {scalar_t__ src; } ;
struct stm32_dfsdm_adc {TYPE_1__* dfsdm; int /*<<< orphan*/  spi_freq; } ;
struct iio_dev {int num_channels; struct iio_chan_spec* channels; int /*<<< orphan*/  dev; } ;
struct iio_chan_spec {size_t channel; int /*<<< orphan*/  info_mask_separate; scalar_t__ scan_index; } ;
struct TYPE_2__ {int /*<<< orphan*/  spi_master_freq; struct stm32_dfsdm_channel* ch_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ DFSDM_CHANNEL_SPI_CLOCK_EXTERNAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IIO_CHAN_INFO_SAMP_FREQ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct iio_chan_spec* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct stm32_dfsdm_adc* iio_priv (struct iio_dev*) ; 
 int stm32_dfsdm_adc_chan_init_one (struct iio_dev*,struct iio_chan_spec*) ; 
 int stm32_dfsdm_dma_request (struct iio_dev*) ; 

__attribute__((used)) static int stm32_dfsdm_audio_init(struct iio_dev *indio_dev)
{
	struct iio_chan_spec *ch;
	struct stm32_dfsdm_adc *adc = iio_priv(indio_dev);
	struct stm32_dfsdm_channel *d_ch;
	int ret;

	ch = devm_kzalloc(&indio_dev->dev, sizeof(*ch), GFP_KERNEL);
	if (!ch)
		return -ENOMEM;

	ch->scan_index = 0;

	ret = stm32_dfsdm_adc_chan_init_one(indio_dev, ch);
	if (ret < 0) {
		dev_err(&indio_dev->dev, "Channels init failed\n");
		return ret;
	}
	ch->info_mask_separate = BIT(IIO_CHAN_INFO_SAMP_FREQ);

	d_ch = &adc->dfsdm->ch_list[ch->channel];
	if (d_ch->src != DFSDM_CHANNEL_SPI_CLOCK_EXTERNAL)
		adc->spi_freq = adc->dfsdm->spi_master_freq;

	indio_dev->num_channels = 1;
	indio_dev->channels = ch;

	return stm32_dfsdm_dma_request(indio_dev);
}