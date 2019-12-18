#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rk_iommu {scalar_t__ num_mmu; int num_irq; int num_clocks; TYPE_2__* clocks; int /*<<< orphan*/  group; int /*<<< orphan*/  iommu; struct device* dev; int /*<<< orphan*/  reset_disabled; int /*<<< orphan*/ * bases; } ;
struct resource {int dummy; } ;
struct device {TYPE_1__* of_node; } ;
struct platform_device {int num_resources; struct device dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_set_iommu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int clk_bulk_prepare (int,TYPE_2__*) ; 
 int /*<<< orphan*/  clk_bulk_unprepare (int,TYPE_2__*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  device_property_read_bool (struct device*,char*) ; 
 int devm_clk_bulk_get (struct device*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct rk_iommu* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rk_iommu*) ; 
 struct device* dma_dev ; 
 int iommu_device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_device_set_fwnode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_device_set_ops (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int iommu_device_sysfs_add (int /*<<< orphan*/ *,struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_device_sysfs_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_group_alloc () ; 
 int /*<<< orphan*/  iommu_group_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_bus_type ; 
 int platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int platform_irq_count (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rk_iommu*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/ * rk_iommu_clocks ; 
 int /*<<< orphan*/  rk_iommu_irq ; 
 int /*<<< orphan*/  rk_iommu_ops ; 

__attribute__((used)) static int rk_iommu_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct rk_iommu *iommu;
	struct resource *res;
	int num_res = pdev->num_resources;
	int err, i;

	iommu = devm_kzalloc(dev, sizeof(*iommu), GFP_KERNEL);
	if (!iommu)
		return -ENOMEM;

	platform_set_drvdata(pdev, iommu);
	iommu->dev = dev;
	iommu->num_mmu = 0;

	iommu->bases = devm_kcalloc(dev, num_res, sizeof(*iommu->bases),
				    GFP_KERNEL);
	if (!iommu->bases)
		return -ENOMEM;

	for (i = 0; i < num_res; i++) {
		res = platform_get_resource(pdev, IORESOURCE_MEM, i);
		if (!res)
			continue;
		iommu->bases[i] = devm_ioremap_resource(&pdev->dev, res);
		if (IS_ERR(iommu->bases[i]))
			continue;
		iommu->num_mmu++;
	}
	if (iommu->num_mmu == 0)
		return PTR_ERR(iommu->bases[0]);

	iommu->num_irq = platform_irq_count(pdev);
	if (iommu->num_irq < 0)
		return iommu->num_irq;

	iommu->reset_disabled = device_property_read_bool(dev,
					"rockchip,disable-mmu-reset");

	iommu->num_clocks = ARRAY_SIZE(rk_iommu_clocks);
	iommu->clocks = devm_kcalloc(iommu->dev, iommu->num_clocks,
				     sizeof(*iommu->clocks), GFP_KERNEL);
	if (!iommu->clocks)
		return -ENOMEM;

	for (i = 0; i < iommu->num_clocks; ++i)
		iommu->clocks[i].id = rk_iommu_clocks[i];

	/*
	 * iommu clocks should be present for all new devices and devicetrees
	 * but there are older devicetrees without clocks out in the wild.
	 * So clocks as optional for the time being.
	 */
	err = devm_clk_bulk_get(iommu->dev, iommu->num_clocks, iommu->clocks);
	if (err == -ENOENT)
		iommu->num_clocks = 0;
	else if (err)
		return err;

	err = clk_bulk_prepare(iommu->num_clocks, iommu->clocks);
	if (err)
		return err;

	iommu->group = iommu_group_alloc();
	if (IS_ERR(iommu->group)) {
		err = PTR_ERR(iommu->group);
		goto err_unprepare_clocks;
	}

	err = iommu_device_sysfs_add(&iommu->iommu, dev, NULL, dev_name(dev));
	if (err)
		goto err_put_group;

	iommu_device_set_ops(&iommu->iommu, &rk_iommu_ops);
	iommu_device_set_fwnode(&iommu->iommu, &dev->of_node->fwnode);

	err = iommu_device_register(&iommu->iommu);
	if (err)
		goto err_remove_sysfs;

	/*
	 * Use the first registered IOMMU device for domain to use with DMA
	 * API, since a domain might not physically correspond to a single
	 * IOMMU device..
	 */
	if (!dma_dev)
		dma_dev = &pdev->dev;

	bus_set_iommu(&platform_bus_type, &rk_iommu_ops);

	pm_runtime_enable(dev);

	for (i = 0; i < iommu->num_irq; i++) {
		int irq = platform_get_irq(pdev, i);

		if (irq < 0)
			return irq;

		err = devm_request_irq(iommu->dev, irq, rk_iommu_irq,
				       IRQF_SHARED, dev_name(dev), iommu);
		if (err) {
			pm_runtime_disable(dev);
			goto err_remove_sysfs;
		}
	}

	return 0;
err_remove_sysfs:
	iommu_device_sysfs_remove(&iommu->iommu);
err_put_group:
	iommu_group_put(iommu->group);
err_unprepare_clocks:
	clk_bulk_unprepare(iommu->num_clocks, iommu->clocks);
	return err;
}