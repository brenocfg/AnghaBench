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
struct bnxt_ring_struct {int nr_pages; int page_size; int /*<<< orphan*/ * vmem; scalar_t__ vmem_size; int /*<<< orphan*/ * dma_arr; int /*<<< orphan*/ * pg_tbl; void** pg_arr; int /*<<< orphan*/  pg_tbl_map; } ;
struct bnxt {struct pci_dev* pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vzalloc (scalar_t__) ; 

__attribute__((used)) static int bnxt_alloc_ring(struct bnxt *bp, struct bnxt_ring_struct *ring)
{
	int i;
	struct pci_dev *pdev = bp->pdev;

	if (ring->nr_pages > 1) {
		ring->pg_tbl = dma_alloc_coherent(&pdev->dev,
						  ring->nr_pages * 8,
						  &ring->pg_tbl_map,
						  GFP_KERNEL);
		if (!ring->pg_tbl)
			return -ENOMEM;
	}

	for (i = 0; i < ring->nr_pages; i++) {
		ring->pg_arr[i] = dma_alloc_coherent(&pdev->dev,
						     ring->page_size,
						     &ring->dma_arr[i],
						     GFP_KERNEL);
		if (!ring->pg_arr[i])
			return -ENOMEM;

		if (ring->nr_pages > 1)
			ring->pg_tbl[i] = cpu_to_le64(ring->dma_arr[i]);
	}

	if (ring->vmem_size) {
		*ring->vmem = vzalloc(ring->vmem_size);
		if (!(*ring->vmem))
			return -ENOMEM;
	}
	return 0;
}