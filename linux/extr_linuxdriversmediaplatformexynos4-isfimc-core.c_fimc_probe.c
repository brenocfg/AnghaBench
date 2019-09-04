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
typedef  scalar_t__ u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {scalar_t__ of_node; } ;
struct platform_device {int id; struct device dev; } ;
struct fimc_dev {int id; int /*<<< orphan*/ * clock; TYPE_1__* drv_data; int /*<<< orphan*/  regs; int /*<<< orphan*/  sysreg; int /*<<< orphan*/  lock; int /*<<< orphan*/  slock; int /*<<< orphan*/  irq_queue; int /*<<< orphan*/  variant; struct platform_device* pdev; } ;
struct TYPE_2__ {int num_entities; scalar_t__ lclk_frequency; int /*<<< orphan*/ * variant; } ;

/* Variables and functions */
 size_t CLK_BUS ; 
 size_t CLK_GATE ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,size_t) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct fimc_dev* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fimc_dev*) ; 
 int fimc_clk_get (struct fimc_dev*) ; 
 int /*<<< orphan*/  fimc_clk_put (struct fimc_dev*) ; 
 TYPE_1__* fimc_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  fimc_get_sysreg_regmap (scalar_t__) ; 
 int fimc_initialize_capture_subdev (struct fimc_dev*) ; 
 int /*<<< orphan*/  fimc_irq_handler ; 
 int fimc_parse_dt (struct fimc_dev*,scalar_t__*) ; 
 int /*<<< orphan*/  fimc_unregister_capture_subdev (struct fimc_dev*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fimc_dev*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enabled (struct device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_dma_contig_set_max_seg_size (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fimc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	u32 lclk_freq = 0;
	struct fimc_dev *fimc;
	struct resource *res;
	int ret = 0;

	fimc = devm_kzalloc(dev, sizeof(*fimc), GFP_KERNEL);
	if (!fimc)
		return -ENOMEM;

	fimc->pdev = pdev;

	if (dev->of_node) {
		ret = fimc_parse_dt(fimc, &lclk_freq);
		if (ret < 0)
			return ret;
	} else {
		fimc->drv_data = fimc_get_drvdata(pdev);
		fimc->id = pdev->id;
	}
	if (!fimc->drv_data || fimc->id >= fimc->drv_data->num_entities ||
	    fimc->id < 0) {
		dev_err(dev, "Invalid driver data or device id (%d)\n",
			fimc->id);
		return -EINVAL;
	}
	if (!dev->of_node)
		fimc->variant = fimc->drv_data->variant[fimc->id];

	init_waitqueue_head(&fimc->irq_queue);
	spin_lock_init(&fimc->slock);
	mutex_init(&fimc->lock);

	fimc->sysreg = fimc_get_sysreg_regmap(dev->of_node);
	if (IS_ERR(fimc->sysreg))
		return PTR_ERR(fimc->sysreg);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	fimc->regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(fimc->regs))
		return PTR_ERR(fimc->regs);

	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (res == NULL) {
		dev_err(dev, "Failed to get IRQ resource\n");
		return -ENXIO;
	}

	ret = fimc_clk_get(fimc);
	if (ret)
		return ret;

	if (lclk_freq == 0)
		lclk_freq = fimc->drv_data->lclk_frequency;

	ret = clk_set_rate(fimc->clock[CLK_BUS], lclk_freq);
	if (ret < 0)
		return ret;

	ret = clk_enable(fimc->clock[CLK_BUS]);
	if (ret < 0)
		return ret;

	ret = devm_request_irq(dev, res->start, fimc_irq_handler,
			       0, dev_name(dev), fimc);
	if (ret < 0) {
		dev_err(dev, "failed to install irq (%d)\n", ret);
		goto err_sclk;
	}

	ret = fimc_initialize_capture_subdev(fimc);
	if (ret < 0)
		goto err_sclk;

	platform_set_drvdata(pdev, fimc);
	pm_runtime_enable(dev);

	if (!pm_runtime_enabled(dev)) {
		ret = clk_enable(fimc->clock[CLK_GATE]);
		if (ret < 0)
			goto err_sd;
	}

	vb2_dma_contig_set_max_seg_size(dev, DMA_BIT_MASK(32));

	dev_dbg(dev, "FIMC.%d registered successfully\n", fimc->id);
	return 0;

err_sd:
	fimc_unregister_capture_subdev(fimc);
err_sclk:
	clk_disable(fimc->clock[CLK_BUS]);
	fimc_clk_put(fimc);
	return ret;
}