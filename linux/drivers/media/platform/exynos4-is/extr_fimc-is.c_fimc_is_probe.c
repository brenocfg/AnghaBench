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
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {struct platform_device* pdev; } ;
struct fimc_is {int /*<<< orphan*/  pmu_regs; int /*<<< orphan*/  irq; int /*<<< orphan*/  regs; int /*<<< orphan*/  lock; int /*<<< orphan*/  slock; int /*<<< orphan*/  irq_queue; TYPE_1__ isp; struct platform_device* pdev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FIMC_IS_FW_FILENAME ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct fimc_is* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_of_platform_populate (struct device*) ; 
 int fimc_is_debugfs_create (struct fimc_is*) ; 
 int /*<<< orphan*/  fimc_is_debugfs_remove (struct fimc_is*) ; 
 int fimc_is_get_clocks (struct fimc_is*) ; 
 int /*<<< orphan*/  fimc_is_irq_handler ; 
 int /*<<< orphan*/  fimc_is_put_clocks (struct fimc_is*) ; 
 int fimc_is_register_subdevs (struct fimc_is*) ; 
 int fimc_is_request_firmware (struct fimc_is*,int /*<<< orphan*/ ) ; 
 int fimc_is_runtime_resume (struct device*) ; 
 int /*<<< orphan*/  fimc_is_runtime_suspend (struct device*) ; 
 int /*<<< orphan*/  fimc_is_unregister_subdevs (struct fimc_is*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct fimc_is*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_of_parse_and_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int of_address_to_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*) ; 
 struct device_node* of_get_child_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fimc_is*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enabled (struct device*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fimc_is*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_dma_contig_set_max_seg_size (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fimc_is_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct fimc_is *is;
	struct resource res;
	struct device_node *node;
	int ret;

	is = devm_kzalloc(&pdev->dev, sizeof(*is), GFP_KERNEL);
	if (!is)
		return -ENOMEM;

	is->pdev = pdev;
	is->isp.pdev = pdev;

	init_waitqueue_head(&is->irq_queue);
	spin_lock_init(&is->slock);
	mutex_init(&is->lock);

	ret = of_address_to_resource(dev->of_node, 0, &res);
	if (ret < 0)
		return ret;

	is->regs = devm_ioremap_resource(dev, &res);
	if (IS_ERR(is->regs))
		return PTR_ERR(is->regs);

	node = of_get_child_by_name(dev->of_node, "pmu");
	if (!node)
		return -ENODEV;

	is->pmu_regs = of_iomap(node, 0);
	of_node_put(node);
	if (!is->pmu_regs)
		return -ENOMEM;

	is->irq = irq_of_parse_and_map(dev->of_node, 0);
	if (!is->irq) {
		dev_err(dev, "no irq found\n");
		ret = -EINVAL;
		goto err_iounmap;
	}

	ret = fimc_is_get_clocks(is);
	if (ret < 0)
		goto err_iounmap;

	platform_set_drvdata(pdev, is);

	ret = request_irq(is->irq, fimc_is_irq_handler, 0, dev_name(dev), is);
	if (ret < 0) {
		dev_err(dev, "irq request failed\n");
		goto err_clk;
	}
	pm_runtime_enable(dev);

	if (!pm_runtime_enabled(dev)) {
		ret = fimc_is_runtime_resume(dev);
		if (ret < 0)
			goto err_irq;
	}

	ret = pm_runtime_get_sync(dev);
	if (ret < 0)
		goto err_pm;

	vb2_dma_contig_set_max_seg_size(dev, DMA_BIT_MASK(32));

	ret = devm_of_platform_populate(dev);
	if (ret < 0)
		goto err_pm;

	/*
	 * Register FIMC-IS V4L2 subdevs to this driver. The video nodes
	 * will be created within the subdev's registered() callback.
	 */
	ret = fimc_is_register_subdevs(is);
	if (ret < 0)
		goto err_pm;

	ret = fimc_is_debugfs_create(is);
	if (ret < 0)
		goto err_sd;

	ret = fimc_is_request_firmware(is, FIMC_IS_FW_FILENAME);
	if (ret < 0)
		goto err_dfs;

	pm_runtime_put_sync(dev);

	dev_dbg(dev, "FIMC-IS registered successfully\n");
	return 0;

err_dfs:
	fimc_is_debugfs_remove(is);
err_sd:
	fimc_is_unregister_subdevs(is);
err_pm:
	if (!pm_runtime_enabled(dev))
		fimc_is_runtime_suspend(dev);
err_irq:
	free_irq(is->irq, is);
err_clk:
	fimc_is_put_clocks(is);
err_iounmap:
	iounmap(is->pmu_regs);
	return ret;
}