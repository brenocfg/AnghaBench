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
typedef  int /*<<< orphan*/  sysmmu_pte_t ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EADDRINUSE ; 
 int SPAGES_PER_LPAGE ; 
 size_t SPAGE_SIZE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dma_dev ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lv2ent_fault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mk_lv2ent_lpage (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mk_lv2ent_spage (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  update_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lv2set_page(sysmmu_pte_t *pent, phys_addr_t paddr, size_t size,
		       int prot, short *pgcnt)
{
	if (size == SPAGE_SIZE) {
		if (WARN_ON(!lv2ent_fault(pent)))
			return -EADDRINUSE;

		update_pte(pent, mk_lv2ent_spage(paddr, prot));
		*pgcnt -= 1;
	} else { /* size == LPAGE_SIZE */
		int i;
		dma_addr_t pent_base = virt_to_phys(pent);

		dma_sync_single_for_cpu(dma_dev, pent_base,
					sizeof(*pent) * SPAGES_PER_LPAGE,
					DMA_TO_DEVICE);
		for (i = 0; i < SPAGES_PER_LPAGE; i++, pent++) {
			if (WARN_ON(!lv2ent_fault(pent))) {
				if (i > 0)
					memset(pent - i, 0, sizeof(*pent) * i);
				return -EADDRINUSE;
			}

			*pent = mk_lv2ent_lpage(paddr, prot);
		}
		dma_sync_single_for_device(dma_dev, pent_base,
					   sizeof(*pent) * SPAGES_PER_LPAGE,
					   DMA_TO_DEVICE);
		*pgcnt -= SPAGES_PER_LPAGE;
	}

	return 0;
}