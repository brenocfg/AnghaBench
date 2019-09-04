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
struct etnaviv_iommuv2_domain {int* mtlb_cpu; int** stlb_cpu; } ;
struct etnaviv_iommu_domain {int dummy; } ;

/* Variables and functions */
 int MMUv2_MAX_STLB_ENTRIES ; 
 int MMUv2_PTE_PRESENT ; 
 int /*<<< orphan*/  SZ_4K ; 
 int /*<<< orphan*/  memcpy (void*,int*,int /*<<< orphan*/ ) ; 
 struct etnaviv_iommuv2_domain* to_etnaviv_domain (struct etnaviv_iommu_domain*) ; 

__attribute__((used)) static void etnaviv_iommuv2_dump(struct etnaviv_iommu_domain *domain, void *buf)
{
	struct etnaviv_iommuv2_domain *etnaviv_domain =
			to_etnaviv_domain(domain);
	int i;

	memcpy(buf, etnaviv_domain->mtlb_cpu, SZ_4K);
	buf += SZ_4K;
	for (i = 0; i < MMUv2_MAX_STLB_ENTRIES; i++, buf += SZ_4K)
		if (etnaviv_domain->mtlb_cpu[i] & MMUv2_PTE_PRESENT)
			memcpy(buf, etnaviv_domain->stlb_cpu[i], SZ_4K);
}