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
struct pasid_entry {int dummy; } ;
struct intel_iommu {int pasid_max; int /*<<< orphan*/ * pasid_state_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 int get_order (int) ; 

int intel_svm_exit(struct intel_iommu *iommu)
{
	int order = get_order(sizeof(struct pasid_entry) * iommu->pasid_max);

	if (iommu->pasid_state_table) {
		free_pages((unsigned long)iommu->pasid_state_table, order);
		iommu->pasid_state_table = NULL;
	}

	return 0;
}