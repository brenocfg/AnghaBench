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
typedef  int u32 ;
struct omap_iommu {int /*<<< orphan*/  pd_dma; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  da ;

/* Variables and functions */
 int IOLARGE_MASK ; 
 size_t IOPGD_SIZE ; 
 int IOPGD_SUPER ; 
 int IOPTE_LARGE ; 
 size_t IOPTE_SIZE ; 
 int IOSUPER_MASK ; 
 int PTRS_PER_IOPTE ; 
 int /*<<< orphan*/  flush_iopte_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int) ; 
 int iopgd_index (int) ; 
 scalar_t__ iopgd_is_table (int) ; 
 int* iopgd_offset (struct omap_iommu*,int) ; 
 int /*<<< orphan*/  iopgd_page_paddr (int*) ; 
 int /*<<< orphan*/  iopte_free (struct omap_iommu*,int*,int) ; 
 int iopte_index (int) ; 
 int* iopte_offset (int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static size_t iopgtable_clear_entry_core(struct omap_iommu *obj, u32 da)
{
	size_t bytes;
	u32 *iopgd = iopgd_offset(obj, da);
	int nent = 1;
	dma_addr_t pt_dma;
	unsigned long pd_offset = iopgd_index(da) * sizeof(da);
	unsigned long pt_offset = iopte_index(da) * sizeof(da);

	if (!*iopgd)
		return 0;

	if (iopgd_is_table(*iopgd)) {
		int i;
		u32 *iopte = iopte_offset(iopgd, da);

		bytes = IOPTE_SIZE;
		if (*iopte & IOPTE_LARGE) {
			nent *= 16;
			/* rewind to the 1st entry */
			iopte = iopte_offset(iopgd, (da & IOLARGE_MASK));
		}
		bytes *= nent;
		memset(iopte, 0, nent * sizeof(*iopte));
		pt_dma = iopgd_page_paddr(iopgd);
		flush_iopte_range(obj->dev, pt_dma, pt_offset, nent);

		/*
		 * do table walk to check if this table is necessary or not
		 */
		iopte = iopte_offset(iopgd, 0);
		for (i = 0; i < PTRS_PER_IOPTE; i++)
			if (iopte[i])
				goto out;

		iopte_free(obj, iopte, true);
		nent = 1; /* for the next L1 entry */
	} else {
		bytes = IOPGD_SIZE;
		if ((*iopgd & IOPGD_SUPER) == IOPGD_SUPER) {
			nent *= 16;
			/* rewind to the 1st entry */
			iopgd = iopgd_offset(obj, (da & IOSUPER_MASK));
		}
		bytes *= nent;
	}
	memset(iopgd, 0, nent * sizeof(*iopgd));
	flush_iopte_range(obj->dev, obj->pd_dma, pd_offset, nent);
out:
	return bytes;
}