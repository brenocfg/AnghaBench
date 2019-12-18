#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stm32_adc_cfg {int /*<<< orphan*/  clk_required; } ;
struct stm32_adc {scalar_t__ irq; TYPE_5__* dma_chan; int /*<<< orphan*/  rx_dma_buf; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/ * clk; struct stm32_adc_cfg const* cfg; int /*<<< orphan*/  offset; int /*<<< orphan*/  completion; int /*<<< orphan*/  lock; int /*<<< orphan*/  common; } ;
struct device {scalar_t__ of_node; TYPE_1__* driver; int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {scalar_t__ of_node; struct device* parent; } ;
struct iio_dev {int modes; int /*<<< orphan*/ * info; TYPE_2__ dev; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {TYPE_3__* device; } ;
struct TYPE_9__ {scalar_t__ data; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_match_table; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int INDIO_DIRECT_MODE ; 
 int INDIO_HARDWARE_TRIGGERED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STM32_ADC_HW_STOP_DELAY_MS ; 
 int /*<<< orphan*/  STM32_DMA_BUFFER_SIZE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/ * devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stm32_adc*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (TYPE_5__*) ; 
 int iio_device_register (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_pollfunc_store_time ; 
 struct stm32_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 TYPE_4__* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int of_property_read_u32 (scalar_t__,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct stm32_adc*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_adc_buffer_setup_ops ; 
 int stm32_adc_chan_of_init (struct iio_dev*) ; 
 int stm32_adc_dma_request (struct iio_dev*) ; 
 int stm32_adc_hw_start (struct device*) ; 
 int /*<<< orphan*/  stm32_adc_hw_stop (struct device*) ; 
 int /*<<< orphan*/  stm32_adc_iio_info ; 
 int /*<<< orphan*/  stm32_adc_isr ; 
 int stm32_adc_of_get_resolution (struct iio_dev*) ; 
 int /*<<< orphan*/  stm32_adc_trigger_handler ; 

__attribute__((used)) static int stm32_adc_probe(struct platform_device *pdev)
{
	struct iio_dev *indio_dev;
	struct device *dev = &pdev->dev;
	struct stm32_adc *adc;
	int ret;

	if (!pdev->dev.of_node)
		return -ENODEV;

	indio_dev = devm_iio_device_alloc(&pdev->dev, sizeof(*adc));
	if (!indio_dev)
		return -ENOMEM;

	adc = iio_priv(indio_dev);
	adc->common = dev_get_drvdata(pdev->dev.parent);
	spin_lock_init(&adc->lock);
	init_completion(&adc->completion);
	adc->cfg = (const struct stm32_adc_cfg *)
		of_match_device(dev->driver->of_match_table, dev)->data;

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->dev.parent = &pdev->dev;
	indio_dev->dev.of_node = pdev->dev.of_node;
	indio_dev->info = &stm32_adc_iio_info;
	indio_dev->modes = INDIO_DIRECT_MODE | INDIO_HARDWARE_TRIGGERED;

	platform_set_drvdata(pdev, adc);

	ret = of_property_read_u32(pdev->dev.of_node, "reg", &adc->offset);
	if (ret != 0) {
		dev_err(&pdev->dev, "missing reg property\n");
		return -EINVAL;
	}

	adc->irq = platform_get_irq(pdev, 0);
	if (adc->irq < 0)
		return adc->irq;

	ret = devm_request_irq(&pdev->dev, adc->irq, stm32_adc_isr,
			       0, pdev->name, adc);
	if (ret) {
		dev_err(&pdev->dev, "failed to request IRQ\n");
		return ret;
	}

	adc->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(adc->clk)) {
		ret = PTR_ERR(adc->clk);
		if (ret == -ENOENT && !adc->cfg->clk_required) {
			adc->clk = NULL;
		} else {
			dev_err(&pdev->dev, "Can't get clock\n");
			return ret;
		}
	}

	ret = stm32_adc_of_get_resolution(indio_dev);
	if (ret < 0)
		return ret;

	ret = stm32_adc_chan_of_init(indio_dev);
	if (ret < 0)
		return ret;

	ret = stm32_adc_dma_request(indio_dev);
	if (ret < 0)
		return ret;

	ret = iio_triggered_buffer_setup(indio_dev,
					 &iio_pollfunc_store_time,
					 &stm32_adc_trigger_handler,
					 &stm32_adc_buffer_setup_ops);
	if (ret) {
		dev_err(&pdev->dev, "buffer setup failed\n");
		goto err_dma_disable;
	}

	/* Get stm32-adc-core PM online */
	pm_runtime_get_noresume(dev);
	pm_runtime_set_active(dev);
	pm_runtime_set_autosuspend_delay(dev, STM32_ADC_HW_STOP_DELAY_MS);
	pm_runtime_use_autosuspend(dev);
	pm_runtime_enable(dev);

	ret = stm32_adc_hw_start(dev);
	if (ret)
		goto err_buffer_cleanup;

	ret = iio_device_register(indio_dev);
	if (ret) {
		dev_err(&pdev->dev, "iio dev register failed\n");
		goto err_hw_stop;
	}

	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);

	return 0;

err_hw_stop:
	stm32_adc_hw_stop(dev);

err_buffer_cleanup:
	pm_runtime_disable(dev);
	pm_runtime_set_suspended(dev);
	pm_runtime_put_noidle(dev);
	iio_triggered_buffer_cleanup(indio_dev);

err_dma_disable:
	if (adc->dma_chan) {
		dma_free_coherent(adc->dma_chan->device->dev,
				  STM32_DMA_BUFFER_SIZE,
				  adc->rx_buf, adc->rx_dma_buf);
		dma_release_channel(adc->dma_chan);
	}

	return ret;
}