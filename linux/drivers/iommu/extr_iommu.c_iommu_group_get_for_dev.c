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
struct iommu_ops {struct iommu_group* (* device_group ) (struct device*) ;} ;
struct iommu_group {struct iommu_domain* domain; struct iommu_domain* default_domain; } ;
struct iommu_domain {int dummy; } ;
struct device {TYPE_1__* bus; } ;
struct TYPE_2__ {struct iommu_ops* iommu_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAIN_ATTR_DMA_USE_FLUSH_QUEUE ; 
 int EINVAL ; 
 struct iommu_group* ERR_PTR (int) ; 
 scalar_t__ IOMMU_DOMAIN_DMA ; 
 scalar_t__ IS_ERR (struct iommu_group*) ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 struct iommu_domain* __iommu_domain_alloc (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,scalar_t__) ; 
 scalar_t__ iommu_def_domain_type ; 
 int /*<<< orphan*/  iommu_dma_strict ; 
 int /*<<< orphan*/  iommu_domain_set_attr (struct iommu_domain*,int /*<<< orphan*/ ,int*) ; 
 int iommu_group_add_device (struct iommu_group*,struct device*) ; 
 struct iommu_group* iommu_group_get (struct device*) ; 
 int /*<<< orphan*/  iommu_group_put (struct iommu_group*) ; 
 struct iommu_group* stub1 (struct device*) ; 

struct iommu_group *iommu_group_get_for_dev(struct device *dev)
{
	const struct iommu_ops *ops = dev->bus->iommu_ops;
	struct iommu_group *group;
	int ret;

	group = iommu_group_get(dev);
	if (group)
		return group;

	if (!ops)
		return ERR_PTR(-EINVAL);

	group = ops->device_group(dev);
	if (WARN_ON_ONCE(group == NULL))
		return ERR_PTR(-EINVAL);

	if (IS_ERR(group))
		return group;

	/*
	 * Try to allocate a default domain - needs support from the
	 * IOMMU driver.
	 */
	if (!group->default_domain) {
		struct iommu_domain *dom;

		dom = __iommu_domain_alloc(dev->bus, iommu_def_domain_type);
		if (!dom && iommu_def_domain_type != IOMMU_DOMAIN_DMA) {
			dom = __iommu_domain_alloc(dev->bus, IOMMU_DOMAIN_DMA);
			if (dom) {
				dev_warn(dev,
					 "failed to allocate default IOMMU domain of type %u; falling back to IOMMU_DOMAIN_DMA",
					 iommu_def_domain_type);
			}
		}

		group->default_domain = dom;
		if (!group->domain)
			group->domain = dom;

		if (dom && !iommu_dma_strict) {
			int attr = 1;
			iommu_domain_set_attr(dom,
					      DOMAIN_ATTR_DMA_USE_FLUSH_QUEUE,
					      &attr);
		}
	}

	ret = iommu_group_add_device(group, dev);
	if (ret) {
		iommu_group_put(group);
		return ERR_PTR(ret);
	}

	return group;
}