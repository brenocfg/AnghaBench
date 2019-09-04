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
struct resource {int /*<<< orphan*/  start; } ;
struct device {int of_node; } ;
struct platform_device {struct device dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct flite_drvdata {scalar_t__ num_instances; } ;
struct fimc_lite {scalar_t__ index; int /*<<< orphan*/  clock; int /*<<< orphan*/  regs; int /*<<< orphan*/  lock; int /*<<< orphan*/  slock; int /*<<< orphan*/  irq_queue; struct platform_device* pdev; struct flite_drvdata* dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct fimc_lite* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fimc_lite*) ; 
 int fimc_lite_clk_get (struct fimc_lite*) ; 
 int /*<<< orphan*/  fimc_lite_clk_put (struct fimc_lite*) ; 
 int fimc_lite_create_capture_subdev (struct fimc_lite*) ; 
 int /*<<< orphan*/  fimc_lite_set_default_config (struct fimc_lite*) ; 
 int /*<<< orphan*/  fimc_lite_unregister_capture_subdev (struct fimc_lite*) ; 
 int /*<<< orphan*/  flite_irq_handler ; 
 int /*<<< orphan*/  flite_of_match ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ of_alias_get_id (int,char*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fimc_lite*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enabled (struct device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_dma_contig_set_max_seg_size (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fimc_lite_probe(struct platform_device *pdev)
{
	struct flite_drvdata *drv_data = NULL;
	struct device *dev = &pdev->dev;
	const struct of_device_id *of_id;
	struct fimc_lite *fimc;
	struct resource *res;
	int ret;

	if (!dev->of_node)
		return -ENODEV;

	fimc = devm_kzalloc(dev, sizeof(*fimc), GFP_KERNEL);
	if (!fimc)
		return -ENOMEM;

	of_id = of_match_node(flite_of_match, dev->of_node);
	if (of_id)
		drv_data = (struct flite_drvdata *)of_id->data;
	fimc->index = of_alias_get_id(dev->of_node, "fimc-lite");

	if (!drv_data || fimc->index >= drv_data->num_instances ||
						fimc->index < 0) {
		dev_err(dev, "Wrong %pOF node alias\n", dev->of_node);
		return -EINVAL;
	}

	fimc->dd = drv_data;
	fimc->pdev = pdev;

	init_waitqueue_head(&fimc->irq_queue);
	spin_lock_init(&fimc->slock);
	mutex_init(&fimc->lock);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	fimc->regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(fimc->regs))
		return PTR_ERR(fimc->regs);

	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (res == NULL) {
		dev_err(dev, "Failed to get IRQ resource\n");
		return -ENXIO;
	}

	ret = fimc_lite_clk_get(fimc);
	if (ret)
		return ret;

	ret = devm_request_irq(dev, res->start, flite_irq_handler,
			       0, dev_name(dev), fimc);
	if (ret) {
		dev_err(dev, "Failed to install irq (%d)\n", ret);
		goto err_clk_put;
	}

	/* The video node will be created within the subdev's registered() op */
	ret = fimc_lite_create_capture_subdev(fimc);
	if (ret)
		goto err_clk_put;

	platform_set_drvdata(pdev, fimc);
	pm_runtime_enable(dev);

	if (!pm_runtime_enabled(dev)) {
		ret = clk_prepare_enable(fimc->clock);
		if (ret < 0)
			goto err_sd;
	}

	vb2_dma_contig_set_max_seg_size(dev, DMA_BIT_MASK(32));

	fimc_lite_set_default_config(fimc);

	dev_dbg(dev, "FIMC-LITE.%d registered successfully\n",
		fimc->index);
	return 0;

err_sd:
	fimc_lite_unregister_capture_subdev(fimc);
err_clk_put:
	fimc_lite_clk_put(fimc);
	return ret;
}