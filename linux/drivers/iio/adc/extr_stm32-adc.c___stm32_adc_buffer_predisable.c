#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stm32_adc {scalar_t__ dma_chan; TYPE_1__* cfg; } ;
struct TYPE_4__ {struct device* parent; } ;
struct iio_dev {TYPE_2__ dev; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* stop_conv ) (struct stm32_adc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dmaengine_terminate_sync (scalar_t__) ; 
 struct stm32_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (struct device*) ; 
 int /*<<< orphan*/  stm32_adc_conv_irq_disable (struct stm32_adc*) ; 
 scalar_t__ stm32_adc_set_trig (struct iio_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct stm32_adc*) ; 

__attribute__((used)) static void __stm32_adc_buffer_predisable(struct iio_dev *indio_dev)
{
	struct stm32_adc *adc = iio_priv(indio_dev);
	struct device *dev = indio_dev->dev.parent;

	adc->cfg->stop_conv(adc);
	if (!adc->dma_chan)
		stm32_adc_conv_irq_disable(adc);

	if (adc->dma_chan)
		dmaengine_terminate_sync(adc->dma_chan);

	if (stm32_adc_set_trig(indio_dev, NULL))
		dev_err(&indio_dev->dev, "Can't clear trigger\n");

	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);
}