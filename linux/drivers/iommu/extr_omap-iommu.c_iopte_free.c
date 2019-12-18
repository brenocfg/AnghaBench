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
struct omap_iommu {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  IOPTE_TABLE_SIZE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iopte_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iopte_free(struct omap_iommu *obj, u32 *iopte, bool dma_valid)
{
	dma_addr_t pt_dma;

	/* Note: freed iopte's must be clean ready for re-use */
	if (iopte) {
		if (dma_valid) {
			pt_dma = virt_to_phys(iopte);
			dma_unmap_single(obj->dev, pt_dma, IOPTE_TABLE_SIZE,
					 DMA_TO_DEVICE);
		}

		kmem_cache_free(iopte_cachep, iopte);
	}
}