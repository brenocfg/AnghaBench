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
struct of_phandle_args {TYPE_1__* np; } ;
struct iommu_ops {int (* of_xlate ) (struct device*,struct of_phandle_args*) ;} ;
struct fwnode_handle {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct fwnode_handle fwnode; } ;

/* Variables and functions */
 int NO_IOMMU ; 
 int driver_deferred_probe_check_state (struct device*) ; 
 int iommu_fwspec_init (struct device*,struct fwnode_handle*,struct iommu_ops const*) ; 
 struct iommu_ops* iommu_ops_from_fwnode (struct fwnode_handle*) ; 
 int /*<<< orphan*/  of_device_is_available (TYPE_1__*) ; 
 int stub1 (struct device*,struct of_phandle_args*) ; 

__attribute__((used)) static int of_iommu_xlate(struct device *dev,
			  struct of_phandle_args *iommu_spec)
{
	const struct iommu_ops *ops;
	struct fwnode_handle *fwnode = &iommu_spec->np->fwnode;
	int err;

	ops = iommu_ops_from_fwnode(fwnode);
	if ((ops && !ops->of_xlate) ||
	    !of_device_is_available(iommu_spec->np))
		return NO_IOMMU;

	err = iommu_fwspec_init(dev, &iommu_spec->np->fwnode, ops);
	if (err)
		return err;
	/*
	 * The otherwise-empty fwspec handily serves to indicate the specific
	 * IOMMU device we're waiting for, which will be useful if we ever get
	 * a proper probe-ordering dependency mechanism in future.
	 */
	if (!ops)
		return driver_deferred_probe_check_state(dev);

	return ops->of_xlate(dev, iommu_spec);
}