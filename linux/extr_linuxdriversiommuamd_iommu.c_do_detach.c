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
typedef  size_t u16 ;
struct protection_domain {int* dev_iommu; int dev_cnt; } ;
struct iommu_dev_data {size_t devid; size_t alias; int /*<<< orphan*/  list; struct protection_domain* domain; } ;
struct amd_iommu {size_t index; } ;

/* Variables and functions */
 struct amd_iommu** amd_iommu_rlookup_table ; 
 int /*<<< orphan*/  clear_dte_entry (size_t) ; 
 int /*<<< orphan*/  device_flush_dte (struct iommu_dev_data*) ; 
 int /*<<< orphan*/  domain_flush_complete (struct protection_domain*) ; 
 int /*<<< orphan*/  domain_flush_tlb_pde (struct protection_domain*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_detach(struct iommu_dev_data *dev_data)
{
	struct protection_domain *domain = dev_data->domain;
	struct amd_iommu *iommu;
	u16 alias;

	iommu = amd_iommu_rlookup_table[dev_data->devid];
	alias = dev_data->alias;

	/* Update data structures */
	dev_data->domain = NULL;
	list_del(&dev_data->list);
	clear_dte_entry(dev_data->devid);
	if (alias != dev_data->devid)
		clear_dte_entry(alias);

	/* Flush the DTE entry */
	device_flush_dte(dev_data);

	/* Flush IOTLB */
	domain_flush_tlb_pde(domain);

	/* Wait for the flushes to finish */
	domain_flush_complete(domain);

	/* decrease reference counters - needs to happen after the flushes */
	domain->dev_iommu[iommu->index] -= 1;
	domain->dev_cnt                 -= 1;
}