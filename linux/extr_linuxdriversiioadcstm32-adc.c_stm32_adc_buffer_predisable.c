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
struct stm32_adc {TYPE_1__* cfg; scalar_t__ dma_chan; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unprepare ) (struct stm32_adc*) ;int /*<<< orphan*/  (* stop_conv ) (struct stm32_adc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (scalar_t__) ; 
 struct stm32_adc* iio_priv (struct iio_dev*) ; 
 int iio_triggered_buffer_predisable (struct iio_dev*) ; 
 int /*<<< orphan*/  stm32_adc_conv_irq_disable (struct stm32_adc*) ; 
 scalar_t__ stm32_adc_set_trig (struct iio_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct stm32_adc*) ; 
 int /*<<< orphan*/  stub2 (struct stm32_adc*) ; 

__attribute__((used)) static int stm32_adc_buffer_predisable(struct iio_dev *indio_dev)
{
	struct stm32_adc *adc = iio_priv(indio_dev);
	int ret;

	adc->cfg->stop_conv(adc);
	if (!adc->dma_chan)
		stm32_adc_conv_irq_disable(adc);

	ret = iio_triggered_buffer_predisable(indio_dev);
	if (ret < 0)
		dev_err(&indio_dev->dev, "predisable failed\n");

	if (adc->dma_chan)
		dmaengine_terminate_all(adc->dma_chan);

	if (stm32_adc_set_trig(indio_dev, NULL))
		dev_err(&indio_dev->dev, "Can't clear trigger\n");

	if (adc->cfg->unprepare)
		adc->cfg->unprepare(adc);

	return ret;
}