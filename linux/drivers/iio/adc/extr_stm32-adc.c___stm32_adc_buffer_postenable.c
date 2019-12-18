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
struct stm32_adc {int /*<<< orphan*/  dma_chan; TYPE_1__* cfg; scalar_t__ bufi; } ;
struct TYPE_4__ {struct device* parent; } ;
struct iio_dev {TYPE_2__ dev; int /*<<< orphan*/ * trig; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* start_conv ) (struct stm32_adc*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 struct stm32_adc* iio_priv (struct iio_dev*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  stm32_adc_conv_irq_enable (struct stm32_adc*) ; 
 int stm32_adc_dma_start (struct iio_dev*) ; 
 int stm32_adc_set_trig (struct iio_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct stm32_adc*,int) ; 

__attribute__((used)) static int __stm32_adc_buffer_postenable(struct iio_dev *indio_dev)
{
	struct stm32_adc *adc = iio_priv(indio_dev);
	struct device *dev = indio_dev->dev.parent;
	int ret;

	ret = pm_runtime_get_sync(dev);
	if (ret < 0) {
		pm_runtime_put_noidle(dev);
		return ret;
	}

	ret = stm32_adc_set_trig(indio_dev, indio_dev->trig);
	if (ret) {
		dev_err(&indio_dev->dev, "Can't set trigger\n");
		goto err_pm_put;
	}

	ret = stm32_adc_dma_start(indio_dev);
	if (ret) {
		dev_err(&indio_dev->dev, "Can't start dma\n");
		goto err_clr_trig;
	}

	/* Reset adc buffer index */
	adc->bufi = 0;

	if (!adc->dma_chan)
		stm32_adc_conv_irq_enable(adc);

	adc->cfg->start_conv(adc, !!adc->dma_chan);

	return 0;

err_clr_trig:
	stm32_adc_set_trig(indio_dev, NULL);
err_pm_put:
	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);

	return ret;
}