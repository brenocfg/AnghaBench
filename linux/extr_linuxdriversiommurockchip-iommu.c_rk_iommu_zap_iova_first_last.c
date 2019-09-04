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
struct rk_iommu_domain {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 size_t SPAGE_SIZE ; 
 int /*<<< orphan*/  rk_iommu_zap_iova (struct rk_iommu_domain*,scalar_t__,size_t) ; 

__attribute__((used)) static void rk_iommu_zap_iova_first_last(struct rk_iommu_domain *rk_domain,
					 dma_addr_t iova, size_t size)
{
	rk_iommu_zap_iova(rk_domain, iova, SPAGE_SIZE);
	if (size > SPAGE_SIZE)
		rk_iommu_zap_iova(rk_domain, iova + size - SPAGE_SIZE,
					SPAGE_SIZE);
}