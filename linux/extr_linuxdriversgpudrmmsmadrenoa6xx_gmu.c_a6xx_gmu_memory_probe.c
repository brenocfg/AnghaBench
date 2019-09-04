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
struct a6xx_gmu {int uncached_iova_base; int /*<<< orphan*/ * domain; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int iommu_attach_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iommu_domain_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_domain_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_bus_type ; 

__attribute__((used)) static int a6xx_gmu_memory_probe(struct a6xx_gmu *gmu)
{
	int ret;

	/*
	 * The GMU address space is hardcoded to treat the range
	 * 0x60000000 - 0x80000000 as un-cached memory. All buffers shared
	 * between the GMU and the CPU will live in this space
	 */
	gmu->uncached_iova_base = 0x60000000;


	gmu->domain = iommu_domain_alloc(&platform_bus_type);
	if (!gmu->domain)
		return -ENODEV;

	ret = iommu_attach_device(gmu->domain, gmu->dev);

	if (ret) {
		iommu_domain_free(gmu->domain);
		gmu->domain = NULL;
	}

	return ret;
}