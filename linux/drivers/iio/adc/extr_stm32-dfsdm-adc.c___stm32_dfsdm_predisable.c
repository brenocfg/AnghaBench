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
struct stm32_dfsdm_adc {scalar_t__ hwc; int /*<<< orphan*/  dfsdm; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_hw_consumer_disable (scalar_t__) ; 
 struct stm32_dfsdm_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  stm32_dfsdm_adc_dma_stop (struct iio_dev*) ; 
 int /*<<< orphan*/  stm32_dfsdm_stop_conv (struct stm32_dfsdm_adc*) ; 
 int /*<<< orphan*/  stm32_dfsdm_stop_dfsdm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __stm32_dfsdm_predisable(struct iio_dev *indio_dev)
{
	struct stm32_dfsdm_adc *adc = iio_priv(indio_dev);

	stm32_dfsdm_stop_conv(adc);

	stm32_dfsdm_adc_dma_stop(indio_dev);

	stm32_dfsdm_stop_dfsdm(adc->dfsdm);

	if (adc->hwc)
		iio_hw_consumer_disable(adc->hwc);
}