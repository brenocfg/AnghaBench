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
typedef  int /*<<< orphan*/  u16 ;
struct intel_iommu {int /*<<< orphan*/  cap; } ;
struct dmar_domain {int /*<<< orphan*/  iovad; } ;

/* Variables and functions */
 int cap_ndoms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpu_cached_iovas (unsigned int,int /*<<< orphan*/ *) ; 
 struct intel_iommu** g_iommus ; 
 int g_num_of_iommus ; 
 struct dmar_domain* get_iommu_domain (struct intel_iommu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_all_cpu_cached_iovas(unsigned int cpu)
{
	int i;

	for (i = 0; i < g_num_of_iommus; i++) {
		struct intel_iommu *iommu = g_iommus[i];
		struct dmar_domain *domain;
		int did;

		if (!iommu)
			continue;

		for (did = 0; did < cap_ndoms(iommu->cap); did++) {
			domain = get_iommu_domain(iommu, (u16)did);

			if (!domain)
				continue;
			free_cpu_cached_iovas(cpu, &domain->iovad);
		}
	}
}