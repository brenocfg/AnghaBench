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
struct pasid_table {int /*<<< orphan*/  order; scalar_t__ table; int /*<<< orphan*/  dev; } ;
struct device_domain_info {struct pasid_table* pasid_table; int /*<<< orphan*/  pasid_supported; } ;
struct TYPE_2__ {struct device_domain_info* iommu; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_is_pci (struct device*) ; 
 int /*<<< orphan*/  device_detach_pasid_table (struct device_domain_info*,struct pasid_table*) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pasid_table*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void intel_pasid_free_table(struct device *dev)
{
	struct device_domain_info *info;
	struct pasid_table *pasid_table;

	info = dev->archdata.iommu;
	if (!info || !dev_is_pci(dev) ||
	    !info->pasid_supported || !info->pasid_table)
		return;

	pasid_table = info->pasid_table;
	device_detach_pasid_table(info, pasid_table);

	if (!list_empty(&pasid_table->dev))
		return;

	free_pages((unsigned long)pasid_table->table, pasid_table->order);
	kfree(pasid_table);
}