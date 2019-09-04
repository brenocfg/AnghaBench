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
struct rk_iommu {int num_mmu; int /*<<< orphan*/ * bases; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  RK_MMU_ZAP_ONE_LINE ; 
 scalar_t__ SPAGE_SIZE ; 
 int /*<<< orphan*/  rk_iommu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rk_iommu_zap_lines(struct rk_iommu *iommu, dma_addr_t iova_start,
			       size_t size)
{
	int i;
	dma_addr_t iova_end = iova_start + size;
	/*
	 * TODO(djkurtz): Figure out when it is more efficient to shootdown the
	 * entire iotlb rather than iterate over individual iovas.
	 */
	for (i = 0; i < iommu->num_mmu; i++) {
		dma_addr_t iova;

		for (iova = iova_start; iova < iova_end; iova += SPAGE_SIZE)
			rk_iommu_write(iommu->bases[i], RK_MMU_ZAP_ONE_LINE, iova);
	}
}