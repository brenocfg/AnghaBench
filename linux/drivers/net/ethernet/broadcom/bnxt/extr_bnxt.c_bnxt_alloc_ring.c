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
typedef  int u64 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct bnxt_ring_mem_info {int flags; int nr_pages; scalar_t__ depth; size_t page_size; int pg_tbl_map; int* dma_arr; int /*<<< orphan*/ * vmem; scalar_t__ vmem_size; int /*<<< orphan*/ * pg_tbl; void** pg_arr; } ;
struct bnxt {struct pci_dev* pdev; } ;

/* Variables and functions */
 int BNXT_RMEM_RING_PTE_FLAG ; 
 int BNXT_RMEM_USE_FULL_PAGE_FLAG ; 
 int BNXT_RMEM_VALID_PTE_FLAG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTU_PTE_LAST ; 
 int PTU_PTE_NEXT_TO_LAST ; 
 int PTU_PTE_VALID ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,size_t,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vzalloc (scalar_t__) ; 

__attribute__((used)) static int bnxt_alloc_ring(struct bnxt *bp, struct bnxt_ring_mem_info *rmem)
{
	struct pci_dev *pdev = bp->pdev;
	u64 valid_bit = 0;
	int i;

	if (rmem->flags & (BNXT_RMEM_VALID_PTE_FLAG | BNXT_RMEM_RING_PTE_FLAG))
		valid_bit = PTU_PTE_VALID;
	if ((rmem->nr_pages > 1 || rmem->depth > 0) && !rmem->pg_tbl) {
		size_t pg_tbl_size = rmem->nr_pages * 8;

		if (rmem->flags & BNXT_RMEM_USE_FULL_PAGE_FLAG)
			pg_tbl_size = rmem->page_size;
		rmem->pg_tbl = dma_alloc_coherent(&pdev->dev, pg_tbl_size,
						  &rmem->pg_tbl_map,
						  GFP_KERNEL);
		if (!rmem->pg_tbl)
			return -ENOMEM;
	}

	for (i = 0; i < rmem->nr_pages; i++) {
		u64 extra_bits = valid_bit;

		rmem->pg_arr[i] = dma_alloc_coherent(&pdev->dev,
						     rmem->page_size,
						     &rmem->dma_arr[i],
						     GFP_KERNEL);
		if (!rmem->pg_arr[i])
			return -ENOMEM;

		if (rmem->nr_pages > 1 || rmem->depth > 0) {
			if (i == rmem->nr_pages - 2 &&
			    (rmem->flags & BNXT_RMEM_RING_PTE_FLAG))
				extra_bits |= PTU_PTE_NEXT_TO_LAST;
			else if (i == rmem->nr_pages - 1 &&
				 (rmem->flags & BNXT_RMEM_RING_PTE_FLAG))
				extra_bits |= PTU_PTE_LAST;
			rmem->pg_tbl[i] =
				cpu_to_le64(rmem->dma_arr[i] | extra_bits);
		}
	}

	if (rmem->vmem_size) {
		*rmem->vmem = vzalloc(rmem->vmem_size);
		if (!(*rmem->vmem))
			return -ENOMEM;
	}
	return 0;
}