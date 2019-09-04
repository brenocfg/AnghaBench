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
struct bnxt_ring_struct {int nr_pages; int page_size; int /*<<< orphan*/ ** vmem; scalar_t__ vmem_size; int /*<<< orphan*/ * pg_tbl; int /*<<< orphan*/  pg_tbl_map; int /*<<< orphan*/ ** pg_arr; int /*<<< orphan*/ * dma_arr; } ;
struct bnxt {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnxt_free_ring(struct bnxt *bp, struct bnxt_ring_struct *ring)
{
	struct pci_dev *pdev = bp->pdev;
	int i;

	for (i = 0; i < ring->nr_pages; i++) {
		if (!ring->pg_arr[i])
			continue;

		dma_free_coherent(&pdev->dev, ring->page_size,
				  ring->pg_arr[i], ring->dma_arr[i]);

		ring->pg_arr[i] = NULL;
	}
	if (ring->pg_tbl) {
		dma_free_coherent(&pdev->dev, ring->nr_pages * 8,
				  ring->pg_tbl, ring->pg_tbl_map);
		ring->pg_tbl = NULL;
	}
	if (ring->vmem_size && *ring->vmem) {
		vfree(*ring->vmem);
		*ring->vmem = NULL;
	}
}