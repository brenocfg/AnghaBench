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
struct sysmmu_drvdata {int /*<<< orphan*/  version; int /*<<< orphan*/  iommu; struct device* sysmmu; int /*<<< orphan*/  lock; int /*<<< orphan*/ * clk_master; int /*<<< orphan*/ * pclk; int /*<<< orphan*/ * aclk; int /*<<< orphan*/ * clk; int /*<<< orphan*/ * sfrbase; } ;
struct resource {int dummy; } ;
struct device {TYPE_1__* of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LV1_PROT ; 
 int /*<<< orphan*/  LV2_PROT ; 
 int MMU_MAJ_VER (int /*<<< orphan*/ ) ; 
 scalar_t__ PG_ENT_SHIFT ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYSMMU_LV1_PROT ; 
 int /*<<< orphan*/  SYSMMU_LV2_PROT ; 
 scalar_t__ SYSMMU_PG_ENT_SHIFT ; 
 int /*<<< orphan*/  SYSMMU_V5_LV1_PROT ; 
 int /*<<< orphan*/  SYSMMU_V5_LV2_PROT ; 
 scalar_t__ SYSMMU_V5_PG_ENT_SHIFT ; 
 int /*<<< orphan*/  __sysmmu_get_version (struct sysmmu_drvdata*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (struct device*,struct resource*) ; 
 struct sysmmu_drvdata* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sysmmu_drvdata*) ; 
 struct device* dma_dev ; 
 int /*<<< orphan*/  exynos_iommu_ops ; 
 int /*<<< orphan*/  exynos_sysmmu_irq ; 
 int iommu_device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_device_set_fwnode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_device_set_ops (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int iommu_device_sysfs_add (int /*<<< orphan*/ *,struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sysmmu_drvdata*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int exynos_sysmmu_probe(struct platform_device *pdev)
{
	int irq, ret;
	struct device *dev = &pdev->dev;
	struct sysmmu_drvdata *data;
	struct resource *res;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	data->sfrbase = devm_ioremap_resource(dev, res);
	if (IS_ERR(data->sfrbase))
		return PTR_ERR(data->sfrbase);

	irq = platform_get_irq(pdev, 0);
	if (irq <= 0)
		return irq;

	ret = devm_request_irq(dev, irq, exynos_sysmmu_irq, 0,
				dev_name(dev), data);
	if (ret) {
		dev_err(dev, "Unabled to register handler of irq %d\n", irq);
		return ret;
	}

	data->clk = devm_clk_get(dev, "sysmmu");
	if (PTR_ERR(data->clk) == -ENOENT)
		data->clk = NULL;
	else if (IS_ERR(data->clk))
		return PTR_ERR(data->clk);

	data->aclk = devm_clk_get(dev, "aclk");
	if (PTR_ERR(data->aclk) == -ENOENT)
		data->aclk = NULL;
	else if (IS_ERR(data->aclk))
		return PTR_ERR(data->aclk);

	data->pclk = devm_clk_get(dev, "pclk");
	if (PTR_ERR(data->pclk) == -ENOENT)
		data->pclk = NULL;
	else if (IS_ERR(data->pclk))
		return PTR_ERR(data->pclk);

	if (!data->clk && (!data->aclk || !data->pclk)) {
		dev_err(dev, "Failed to get device clock(s)!\n");
		return -ENOSYS;
	}

	data->clk_master = devm_clk_get(dev, "master");
	if (PTR_ERR(data->clk_master) == -ENOENT)
		data->clk_master = NULL;
	else if (IS_ERR(data->clk_master))
		return PTR_ERR(data->clk_master);

	data->sysmmu = dev;
	spin_lock_init(&data->lock);

	ret = iommu_device_sysfs_add(&data->iommu, &pdev->dev, NULL,
				     dev_name(data->sysmmu));
	if (ret)
		return ret;

	iommu_device_set_ops(&data->iommu, &exynos_iommu_ops);
	iommu_device_set_fwnode(&data->iommu, &dev->of_node->fwnode);

	ret = iommu_device_register(&data->iommu);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, data);

	__sysmmu_get_version(data);
	if (PG_ENT_SHIFT < 0) {
		if (MMU_MAJ_VER(data->version) < 5) {
			PG_ENT_SHIFT = SYSMMU_PG_ENT_SHIFT;
			LV1_PROT = SYSMMU_LV1_PROT;
			LV2_PROT = SYSMMU_LV2_PROT;
		} else {
			PG_ENT_SHIFT = SYSMMU_V5_PG_ENT_SHIFT;
			LV1_PROT = SYSMMU_V5_LV1_PROT;
			LV2_PROT = SYSMMU_V5_LV2_PROT;
		}
	}

	/*
	 * use the first registered sysmmu device for performing
	 * dma mapping operations on iommu page tables (cpu cache flush)
	 */
	if (!dma_dev)
		dma_dev = &pdev->dev;

	pm_runtime_enable(dev);

	return 0;
}