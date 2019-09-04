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
struct protection_domain {int /*<<< orphan*/ * dev_iommu; } ;

/* Variables and functions */
 int amd_iommu_get_num_iommus () ; 
 int /*<<< orphan*/ * amd_iommus ; 
 int /*<<< orphan*/  iommu_completion_wait (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void domain_flush_complete(struct protection_domain *domain)
{
	int i;

	for (i = 0; i < amd_iommu_get_num_iommus(); ++i) {
		if (domain && !domain->dev_iommu[i])
			continue;

		/*
		 * Devices of this domain are behind this IOMMU
		 * We need to wait for completion of all commands.
		 */
		iommu_completion_wait(amd_iommus[i]);
	}
}