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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct bnxt_ring_mem_info {int nr_pages; size_t page_size; int flags; int /*<<< orphan*/ ** vmem; scalar_t__ vmem_size; int /*<<< orphan*/ * pg_tbl; int /*<<< orphan*/  pg_tbl_map; int /*<<< orphan*/ ** pg_arr; int /*<<< orphan*/ * dma_arr; } ;
struct bnxt {struct pci_dev* pdev; } ;

/* Variables and functions */
 int BNXT_RMEM_USE_FULL_PAGE_FLAG ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnxt_free_ring(struct bnxt *bp, struct bnxt_ring_mem_info *rmem)
{
	struct pci_dev *pdev = bp->pdev;
	int i;

	for (i = 0; i < rmem->nr_pages; i++) {
		if (!rmem->pg_arr[i])
			continue;

		dma_free_coherent(&pdev->dev, rmem->page_size,
				  rmem->pg_arr[i], rmem->dma_arr[i]);

		rmem->pg_arr[i] = NULL;
	}
	if (rmem->pg_tbl) {
		size_t pg_tbl_size = rmem->nr_pages * 8;

		if (rmem->flags & BNXT_RMEM_USE_FULL_PAGE_FLAG)
			pg_tbl_size = rmem->page_size;
		dma_free_coherent(&pdev->dev, pg_tbl_size,
				  rmem->pg_tbl, rmem->pg_tbl_map);
		rmem->pg_tbl = NULL;
	}
	if (rmem->vmem_size && *rmem->vmem) {
		vfree(*rmem->vmem);
		*rmem->vmem = NULL;
	}
}