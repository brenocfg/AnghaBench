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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_mc {scalar_t__ regs; } ;
struct resource {scalar_t__ end; int /*<<< orphan*/  start; } ;
struct gart_device {int /*<<< orphan*/  iommu; int /*<<< orphan*/  savedata; int /*<<< orphan*/  dom_lock; int /*<<< orphan*/  pte_lock; scalar_t__ iovmm_end; int /*<<< orphan*/  iovmm_base; scalar_t__ regs; struct device* dev; } ;
struct device {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 int ENXIO ; 
 struct gart_device* ERR_PTR (int) ; 
 scalar_t__ GART_PAGE_SHIFT ; 
 int GART_PAGE_SIZE ; 
 scalar_t__ GART_REG_BASE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ PAGE_SHIFT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  do_gart_setup (struct gart_device*,int /*<<< orphan*/ *) ; 
 struct gart_device* gart_handle ; 
 int /*<<< orphan*/  gart_iommu_ops ; 
 int iommu_device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_device_set_fwnode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_device_set_ops (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int iommu_device_sysfs_add (int /*<<< orphan*/ *,struct device*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iommu_device_sysfs_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct gart_device*) ; 
 struct gart_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_platform_device (struct device*) ; 
 int /*<<< orphan*/  vmalloc (int) ; 

struct gart_device *tegra_gart_probe(struct device *dev, struct tegra_mc *mc)
{
	struct gart_device *gart;
	struct resource *res;
	int err;

	BUILD_BUG_ON(PAGE_SHIFT != GART_PAGE_SHIFT);

	/* the GART memory aperture is required */
	res = platform_get_resource(to_platform_device(dev), IORESOURCE_MEM, 1);
	if (!res) {
		dev_err(dev, "Memory aperture resource unavailable\n");
		return ERR_PTR(-ENXIO);
	}

	gart = kzalloc(sizeof(*gart), GFP_KERNEL);
	if (!gart)
		return ERR_PTR(-ENOMEM);

	gart_handle = gart;

	gart->dev = dev;
	gart->regs = mc->regs + GART_REG_BASE;
	gart->iovmm_base = res->start;
	gart->iovmm_end = res->end + 1;
	spin_lock_init(&gart->pte_lock);
	spin_lock_init(&gart->dom_lock);

	do_gart_setup(gart, NULL);

	err = iommu_device_sysfs_add(&gart->iommu, dev, NULL, "gart");
	if (err)
		goto free_gart;

	iommu_device_set_ops(&gart->iommu, &gart_iommu_ops);
	iommu_device_set_fwnode(&gart->iommu, dev->fwnode);

	err = iommu_device_register(&gart->iommu);
	if (err)
		goto remove_sysfs;

	gart->savedata = vmalloc(resource_size(res) / GART_PAGE_SIZE *
				 sizeof(u32));
	if (!gart->savedata) {
		err = -ENOMEM;
		goto unregister_iommu;
	}

	return gart;

unregister_iommu:
	iommu_device_unregister(&gart->iommu);
remove_sysfs:
	iommu_device_sysfs_remove(&gart->iommu);
free_gart:
	kfree(gart);

	return ERR_PTR(err);
}