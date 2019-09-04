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
struct stm32_dfsdm_adc {int /*<<< orphan*/  dfsdm; scalar_t__ dma_chan; scalar_t__ bufi; } ;
struct iio_dev {int /*<<< orphan*/  dev; struct iio_chan_spec* channels; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct stm32_dfsdm_adc* iio_priv (struct iio_dev*) ; 
 int stm32_dfsdm_adc_dma_start (struct iio_dev*) ; 
 int stm32_dfsdm_start_conv (struct stm32_dfsdm_adc*,struct iio_chan_spec const*,int) ; 
 int stm32_dfsdm_start_dfsdm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_dfsdm_stop_conv (struct stm32_dfsdm_adc*,struct iio_chan_spec const*) ; 
 int /*<<< orphan*/  stm32_dfsdm_stop_dfsdm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_dfsdm_postenable(struct iio_dev *indio_dev)
{
	struct stm32_dfsdm_adc *adc = iio_priv(indio_dev);
	const struct iio_chan_spec *chan = &indio_dev->channels[0];
	int ret;

	/* Reset adc buffer index */
	adc->bufi = 0;

	ret = stm32_dfsdm_start_dfsdm(adc->dfsdm);
	if (ret < 0)
		return ret;

	ret = stm32_dfsdm_start_conv(adc, chan, true);
	if (ret) {
		dev_err(&indio_dev->dev, "Can't start conversion\n");
		goto stop_dfsdm;
	}

	if (adc->dma_chan) {
		ret = stm32_dfsdm_adc_dma_start(indio_dev);
		if (ret) {
			dev_err(&indio_dev->dev, "Can't start DMA\n");
			goto err_stop_conv;
		}
	}

	return 0;

err_stop_conv:
	stm32_dfsdm_stop_conv(adc, chan);
stop_dfsdm:
	stm32_dfsdm_stop_dfsdm(adc->dfsdm);

	return ret;
}