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
struct bus_type {struct iommu_ops const* iommu_ops; } ;

/* Variables and functions */
 int EBUSY ; 
 int iommu_bus_init (struct bus_type*,struct iommu_ops const*) ; 

int bus_set_iommu(struct bus_type *bus, const struct iommu_ops *ops)
{
	int err;

	if (bus->iommu_ops != NULL)
		return -EBUSY;

	bus->iommu_ops = ops;

	/* Do IOMMU specific setup for this bus-type */
	err = iommu_bus_init(bus, ops);
	if (err)
		bus->iommu_ops = NULL;

	return err;
}