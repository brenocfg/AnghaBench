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
struct stm32_dfsdm_adc {scalar_t__ hwc; int /*<<< orphan*/  dfsdm; scalar_t__ bufi; } ;
struct iio_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  trig; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iio_hw_consumer_disable (scalar_t__) ; 
 int iio_hw_consumer_enable (scalar_t__) ; 
 struct stm32_dfsdm_adc* iio_priv (struct iio_dev*) ; 
 int stm32_dfsdm_adc_dma_start (struct iio_dev*) ; 
 int /*<<< orphan*/  stm32_dfsdm_adc_dma_stop (struct iio_dev*) ; 
 int stm32_dfsdm_start_conv (struct stm32_dfsdm_adc*,int /*<<< orphan*/ ) ; 
 int stm32_dfsdm_start_dfsdm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_dfsdm_stop_dfsdm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __stm32_dfsdm_postenable(struct iio_dev *indio_dev)
{
	struct stm32_dfsdm_adc *adc = iio_priv(indio_dev);
	int ret;

	/* Reset adc buffer index */
	adc->bufi = 0;

	if (adc->hwc) {
		ret = iio_hw_consumer_enable(adc->hwc);
		if (ret < 0)
			return ret;
	}

	ret = stm32_dfsdm_start_dfsdm(adc->dfsdm);
	if (ret < 0)
		goto err_stop_hwc;

	ret = stm32_dfsdm_adc_dma_start(indio_dev);
	if (ret) {
		dev_err(&indio_dev->dev, "Can't start DMA\n");
		goto stop_dfsdm;
	}

	ret = stm32_dfsdm_start_conv(adc, indio_dev->trig);
	if (ret) {
		dev_err(&indio_dev->dev, "Can't start conversion\n");
		goto err_stop_dma;
	}

	return 0;

err_stop_dma:
	stm32_dfsdm_adc_dma_stop(indio_dev);
stop_dfsdm:
	stm32_dfsdm_stop_dfsdm(adc->dfsdm);
err_stop_hwc:
	if (adc->hwc)
		iio_hw_consumer_disable(adc->hwc);

	return ret;
}