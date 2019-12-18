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
struct venus_core {scalar_t__ irq; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  work; int /*<<< orphan*/  lock; int /*<<< orphan*/  instances; TYPE_1__* res; int /*<<< orphan*/  base; struct device* dev; } ;
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; void* dma_parms; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDC_SESSION_TYPE_DEC ; 
 int /*<<< orphan*/  VIDC_SESSION_TYPE_ENC ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct venus_core*) ; 
 int dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_set_max_seg_size (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi_core_deinit (struct venus_core*,int) ; 
 int hfi_core_init (struct venus_core*) ; 
 int hfi_core_resume (struct venus_core*,int) ; 
 int hfi_create (struct venus_core*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfi_destroy (struct venus_core*) ; 
 int /*<<< orphan*/  hfi_isr ; 
 int /*<<< orphan*/  hfi_isr_thread ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* of_device_get_match_data (struct device*) ; 
 int of_platform_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct venus_core*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (struct device*) ; 
 int v4l2_device_register (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int venus_boot (struct venus_core*) ; 
 int venus_clks_get (struct venus_core*) ; 
 int /*<<< orphan*/  venus_core_ops ; 
 int venus_enumerate_codecs (struct venus_core*,int /*<<< orphan*/ ) ; 
 int venus_firmware_init (struct venus_core*) ; 
 int /*<<< orphan*/  venus_shutdown (struct venus_core*) ; 
 int /*<<< orphan*/  venus_sys_error_handler ; 

__attribute__((used)) static int venus_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct venus_core *core;
	struct resource *r;
	int ret;

	core = devm_kzalloc(dev, sizeof(*core), GFP_KERNEL);
	if (!core)
		return -ENOMEM;

	core->dev = dev;
	platform_set_drvdata(pdev, core);

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	core->base = devm_ioremap_resource(dev, r);
	if (IS_ERR(core->base))
		return PTR_ERR(core->base);

	core->irq = platform_get_irq(pdev, 0);
	if (core->irq < 0)
		return core->irq;

	core->res = of_device_get_match_data(dev);
	if (!core->res)
		return -ENODEV;

	ret = venus_clks_get(core);
	if (ret)
		return ret;

	ret = dma_set_mask_and_coherent(dev, core->res->dma_mask);
	if (ret)
		return ret;

	if (!dev->dma_parms) {
		dev->dma_parms = devm_kzalloc(dev, sizeof(*dev->dma_parms),
					      GFP_KERNEL);
		if (!dev->dma_parms)
			return -ENOMEM;
	}
	dma_set_max_seg_size(dev, DMA_BIT_MASK(32));

	INIT_LIST_HEAD(&core->instances);
	mutex_init(&core->lock);
	INIT_DELAYED_WORK(&core->work, venus_sys_error_handler);

	ret = devm_request_threaded_irq(dev, core->irq, hfi_isr, hfi_isr_thread,
					IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					"venus", core);
	if (ret)
		return ret;

	ret = hfi_create(core, &venus_core_ops);
	if (ret)
		return ret;

	pm_runtime_enable(dev);

	ret = pm_runtime_get_sync(dev);
	if (ret < 0)
		goto err_runtime_disable;

	ret = of_platform_populate(dev->of_node, NULL, NULL, dev);
	if (ret)
		goto err_runtime_disable;

	ret = venus_firmware_init(core);
	if (ret)
		goto err_runtime_disable;

	ret = venus_boot(core);
	if (ret)
		goto err_runtime_disable;

	ret = hfi_core_resume(core, true);
	if (ret)
		goto err_venus_shutdown;

	ret = hfi_core_init(core);
	if (ret)
		goto err_venus_shutdown;

	ret = venus_enumerate_codecs(core, VIDC_SESSION_TYPE_DEC);
	if (ret)
		goto err_venus_shutdown;

	ret = venus_enumerate_codecs(core, VIDC_SESSION_TYPE_ENC);
	if (ret)
		goto err_venus_shutdown;

	ret = v4l2_device_register(dev, &core->v4l2_dev);
	if (ret)
		goto err_core_deinit;

	ret = pm_runtime_put_sync(dev);
	if (ret)
		goto err_dev_unregister;

	return 0;

err_dev_unregister:
	v4l2_device_unregister(&core->v4l2_dev);
err_core_deinit:
	hfi_core_deinit(core, false);
err_venus_shutdown:
	venus_shutdown(core);
err_runtime_disable:
	pm_runtime_set_suspended(dev);
	pm_runtime_disable(dev);
	hfi_destroy(core);
	return ret;
}