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
typedef  int /*<<< orphan*/  u32 ;
struct rk_iommu_domain {int /*<<< orphan*/  dt_lock; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 size_t SPAGE_SIZE ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rk_mk_pte_invalid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_pte_is_page_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_table_flush (struct rk_iommu_domain*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static size_t rk_iommu_unmap_iova(struct rk_iommu_domain *rk_domain,
				  u32 *pte_addr, dma_addr_t pte_dma,
				  size_t size)
{
	unsigned int pte_count;
	unsigned int pte_total = size / SPAGE_SIZE;

	assert_spin_locked(&rk_domain->dt_lock);

	for (pte_count = 0; pte_count < pte_total; pte_count++) {
		u32 pte = pte_addr[pte_count];
		if (!rk_pte_is_page_valid(pte))
			break;

		pte_addr[pte_count] = rk_mk_pte_invalid(pte);
	}

	rk_table_flush(rk_domain, pte_dma, pte_count);

	return pte_count * SPAGE_SIZE;
}