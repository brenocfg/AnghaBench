#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* name; struct device* parent; int /*<<< orphan*/ * fops; int /*<<< orphan*/  minor; } ;
struct tegra_vde {int /*<<< orphan*/  iram_pool; scalar_t__ iram; TYPE_1__ miscdev; int /*<<< orphan*/  decode_completion; int /*<<< orphan*/  lock; int /*<<< orphan*/  map_lock; int /*<<< orphan*/  map_list; int /*<<< orphan*/  iram_lists_addr; void* rst_mc; void* rst; void* clk; void* frameid; void* vdma; void* ppb; void* tfe; void* mce; void* ppe; void* mbe; void* bsev; void* sxe; } ;
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  MISC_DYNAMIC_MINOR ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 void* devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct tegra_vde* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tegra_vde*) ; 
 void* devm_reset_control_get (struct device*,int /*<<< orphan*/ *) ; 
 void* devm_reset_control_get_optional (struct device*,char*) ; 
 scalar_t__ gen_pool_dma_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_pool_free (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_pool_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  misc_deregister (TYPE_1__*) ; 
 int misc_register (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_gen_pool_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tegra_vde*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enabled (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  tegra_vde_fops ; 
 int /*<<< orphan*/  tegra_vde_iommu_deinit (struct tegra_vde*) ; 
 int tegra_vde_iommu_init (struct tegra_vde*) ; 
 int /*<<< orphan*/  tegra_vde_isr ; 
 int tegra_vde_runtime_resume (struct device*) ; 

__attribute__((used)) static int tegra_vde_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *regs;
	struct tegra_vde *vde;
	int irq, err;

	vde = devm_kzalloc(dev, sizeof(*vde), GFP_KERNEL);
	if (!vde)
		return -ENOMEM;

	platform_set_drvdata(pdev, vde);

	regs = platform_get_resource_byname(pdev, IORESOURCE_MEM, "sxe");
	if (!regs)
		return -ENODEV;

	vde->sxe = devm_ioremap_resource(dev, regs);
	if (IS_ERR(vde->sxe))
		return PTR_ERR(vde->sxe);

	regs = platform_get_resource_byname(pdev, IORESOURCE_MEM, "bsev");
	if (!regs)
		return -ENODEV;

	vde->bsev = devm_ioremap_resource(dev, regs);
	if (IS_ERR(vde->bsev))
		return PTR_ERR(vde->bsev);

	regs = platform_get_resource_byname(pdev, IORESOURCE_MEM, "mbe");
	if (!regs)
		return -ENODEV;

	vde->mbe = devm_ioremap_resource(dev, regs);
	if (IS_ERR(vde->mbe))
		return PTR_ERR(vde->mbe);

	regs = platform_get_resource_byname(pdev, IORESOURCE_MEM, "ppe");
	if (!regs)
		return -ENODEV;

	vde->ppe = devm_ioremap_resource(dev, regs);
	if (IS_ERR(vde->ppe))
		return PTR_ERR(vde->ppe);

	regs = platform_get_resource_byname(pdev, IORESOURCE_MEM, "mce");
	if (!regs)
		return -ENODEV;

	vde->mce = devm_ioremap_resource(dev, regs);
	if (IS_ERR(vde->mce))
		return PTR_ERR(vde->mce);

	regs = platform_get_resource_byname(pdev, IORESOURCE_MEM, "tfe");
	if (!regs)
		return -ENODEV;

	vde->tfe = devm_ioremap_resource(dev, regs);
	if (IS_ERR(vde->tfe))
		return PTR_ERR(vde->tfe);

	regs = platform_get_resource_byname(pdev, IORESOURCE_MEM, "ppb");
	if (!regs)
		return -ENODEV;

	vde->ppb = devm_ioremap_resource(dev, regs);
	if (IS_ERR(vde->ppb))
		return PTR_ERR(vde->ppb);

	regs = platform_get_resource_byname(pdev, IORESOURCE_MEM, "vdma");
	if (!regs)
		return -ENODEV;

	vde->vdma = devm_ioremap_resource(dev, regs);
	if (IS_ERR(vde->vdma))
		return PTR_ERR(vde->vdma);

	regs = platform_get_resource_byname(pdev, IORESOURCE_MEM, "frameid");
	if (!regs)
		return -ENODEV;

	vde->frameid = devm_ioremap_resource(dev, regs);
	if (IS_ERR(vde->frameid))
		return PTR_ERR(vde->frameid);

	vde->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(vde->clk)) {
		err = PTR_ERR(vde->clk);
		dev_err(dev, "Could not get VDE clk %d\n", err);
		return err;
	}

	vde->rst = devm_reset_control_get(dev, NULL);
	if (IS_ERR(vde->rst)) {
		err = PTR_ERR(vde->rst);
		dev_err(dev, "Could not get VDE reset %d\n", err);
		return err;
	}

	vde->rst_mc = devm_reset_control_get_optional(dev, "mc");
	if (IS_ERR(vde->rst_mc)) {
		err = PTR_ERR(vde->rst_mc);
		dev_err(dev, "Could not get MC reset %d\n", err);
		return err;
	}

	irq = platform_get_irq_byname(pdev, "sync-token");
	if (irq < 0)
		return irq;

	err = devm_request_irq(dev, irq, tegra_vde_isr, 0,
			       dev_name(dev), vde);
	if (err) {
		dev_err(dev, "Could not request IRQ %d\n", err);
		return err;
	}

	vde->iram_pool = of_gen_pool_get(dev->of_node, "iram", 0);
	if (!vde->iram_pool) {
		dev_err(dev, "Could not get IRAM pool\n");
		return -EPROBE_DEFER;
	}

	vde->iram = gen_pool_dma_alloc(vde->iram_pool,
				       gen_pool_size(vde->iram_pool),
				       &vde->iram_lists_addr);
	if (!vde->iram) {
		dev_err(dev, "Could not reserve IRAM\n");
		return -ENOMEM;
	}

	INIT_LIST_HEAD(&vde->map_list);
	mutex_init(&vde->map_lock);
	mutex_init(&vde->lock);
	init_completion(&vde->decode_completion);

	vde->miscdev.minor = MISC_DYNAMIC_MINOR;
	vde->miscdev.name = "tegra_vde";
	vde->miscdev.fops = &tegra_vde_fops;
	vde->miscdev.parent = dev;

	err = tegra_vde_iommu_init(vde);
	if (err) {
		dev_err(dev, "Failed to initialize IOMMU: %d\n", err);
		goto err_gen_free;
	}

	err = misc_register(&vde->miscdev);
	if (err) {
		dev_err(dev, "Failed to register misc device: %d\n", err);
		goto err_deinit_iommu;
	}

	pm_runtime_enable(dev);
	pm_runtime_use_autosuspend(dev);
	pm_runtime_set_autosuspend_delay(dev, 300);

	if (!pm_runtime_enabled(dev)) {
		err = tegra_vde_runtime_resume(dev);
		if (err)
			goto err_misc_unreg;
	}

	return 0;

err_misc_unreg:
	misc_deregister(&vde->miscdev);

err_deinit_iommu:
	tegra_vde_iommu_deinit(vde);

err_gen_free:
	gen_pool_free(vde->iram_pool, (unsigned long)vde->iram,
		      gen_pool_size(vde->iram_pool));

	return err;
}