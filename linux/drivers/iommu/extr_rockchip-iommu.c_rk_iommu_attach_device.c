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
struct rk_iommu_domain {int /*<<< orphan*/  iommus_lock; int /*<<< orphan*/  iommus; } ;
struct rk_iommu {int /*<<< orphan*/  dev; struct iommu_domain* domain; int /*<<< orphan*/  node; } ;
struct iommu_domain {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pm_runtime_get_if_in_use (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_iommu_detach_device (struct iommu_domain*,struct device*) ; 
 int rk_iommu_enable (struct rk_iommu*) ; 
 struct rk_iommu* rk_iommu_from_dev (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct rk_iommu_domain* to_rk_domain (struct iommu_domain*) ; 

__attribute__((used)) static int rk_iommu_attach_device(struct iommu_domain *domain,
		struct device *dev)
{
	struct rk_iommu *iommu;
	struct rk_iommu_domain *rk_domain = to_rk_domain(domain);
	unsigned long flags;
	int ret;

	/*
	 * Allow 'virtual devices' (e.g., drm) to attach to domain.
	 * Such a device does not belong to an iommu group.
	 */
	iommu = rk_iommu_from_dev(dev);
	if (!iommu)
		return 0;

	dev_dbg(dev, "Attaching to iommu domain\n");

	/* iommu already attached */
	if (iommu->domain == domain)
		return 0;

	if (iommu->domain)
		rk_iommu_detach_device(iommu->domain, dev);

	iommu->domain = domain;

	spin_lock_irqsave(&rk_domain->iommus_lock, flags);
	list_add_tail(&iommu->node, &rk_domain->iommus);
	spin_unlock_irqrestore(&rk_domain->iommus_lock, flags);

	ret = pm_runtime_get_if_in_use(iommu->dev);
	if (!ret || WARN_ON_ONCE(ret < 0))
		return 0;

	ret = rk_iommu_enable(iommu);
	if (ret)
		rk_iommu_detach_device(iommu->domain, dev);

	pm_runtime_put(iommu->dev);

	return ret;
}