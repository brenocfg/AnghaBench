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
struct iommu_domain {int /*<<< orphan*/  pgsize_bitmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned long __ffs (int /*<<< orphan*/ ) ; 
 struct iommu_domain* iommu_get_dma_domain (struct device*) ; 

__attribute__((used)) static unsigned long iommu_dma_get_merge_boundary(struct device *dev)
{
	struct iommu_domain *domain = iommu_get_dma_domain(dev);

	return (1UL << __ffs(domain->pgsize_bitmap)) - 1;
}