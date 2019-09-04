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
struct rk_iommu_domain {int /*<<< orphan*/  iommus_lock; } ;
struct rk_iommu {int /*<<< orphan*/  dev; int /*<<< orphan*/  node; struct iommu_domain* domain; } ;
struct iommu_domain {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_if_in_use (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_iommu_disable (struct rk_iommu*) ; 
 struct rk_iommu* rk_iommu_from_dev (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct rk_iommu_domain* to_rk_domain (struct iommu_domain*) ; 

__attribute__((used)) static void rk_iommu_detach_device(struct iommu_domain *domain,
				   struct device *dev)
{
	struct rk_iommu *iommu;
	struct rk_iommu_domain *rk_domain = to_rk_domain(domain);
	unsigned long flags;
	int ret;

	/* Allow 'virtual devices' (eg drm) to detach from domain */
	iommu = rk_iommu_from_dev(dev);
	if (!iommu)
		return;

	dev_dbg(dev, "Detaching from iommu domain\n");

	/* iommu already detached */
	if (iommu->domain != domain)
		return;

	iommu->domain = NULL;

	spin_lock_irqsave(&rk_domain->iommus_lock, flags);
	list_del_init(&iommu->node);
	spin_unlock_irqrestore(&rk_domain->iommus_lock, flags);

	ret = pm_runtime_get_if_in_use(iommu->dev);
	WARN_ON_ONCE(ret < 0);
	if (ret > 0) {
		rk_iommu_disable(iommu);
		pm_runtime_put(iommu->dev);
	}
}