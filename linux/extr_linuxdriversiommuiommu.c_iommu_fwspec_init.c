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
struct iommu_ops {int dummy; } ;
struct iommu_fwspec {struct iommu_ops const* ops; struct fwnode_handle* iommu_fwnode; } ;
struct fwnode_handle {int dummy; } ;
struct device {struct iommu_fwspec* iommu_fwspec; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct iommu_fwspec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_of_node (struct fwnode_handle*) ; 

int iommu_fwspec_init(struct device *dev, struct fwnode_handle *iommu_fwnode,
		      const struct iommu_ops *ops)
{
	struct iommu_fwspec *fwspec = dev->iommu_fwspec;

	if (fwspec)
		return ops == fwspec->ops ? 0 : -EINVAL;

	fwspec = kzalloc(sizeof(*fwspec), GFP_KERNEL);
	if (!fwspec)
		return -ENOMEM;

	of_node_get(to_of_node(iommu_fwnode));
	fwspec->iommu_fwnode = iommu_fwnode;
	fwspec->ops = ops;
	dev->iommu_fwspec = fwspec;
	return 0;
}