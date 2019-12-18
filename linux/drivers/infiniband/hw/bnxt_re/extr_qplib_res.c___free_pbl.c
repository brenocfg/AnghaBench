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
struct bnxt_qplib_pbl {int pg_count; scalar_t__ pg_size; int /*<<< orphan*/ ** pg_map_arr; int /*<<< orphan*/ ** pg_arr; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,scalar_t__,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void __free_pbl(struct pci_dev *pdev, struct bnxt_qplib_pbl *pbl,
		       bool is_umem)
{
	int i;

	if (!is_umem) {
		for (i = 0; i < pbl->pg_count; i++) {
			if (pbl->pg_arr[i])
				dma_free_coherent(&pdev->dev, pbl->pg_size,
						  (void *)((unsigned long)
						   pbl->pg_arr[i] &
						  PAGE_MASK),
						  pbl->pg_map_arr[i]);
			else
				dev_warn(&pdev->dev,
					 "PBL free pg_arr[%d] empty?!\n", i);
			pbl->pg_arr[i] = NULL;
		}
	}
	kfree(pbl->pg_arr);
	pbl->pg_arr = NULL;
	kfree(pbl->pg_map_arr);
	pbl->pg_map_arr = NULL;
	pbl->pg_count = 0;
	pbl->pg_size = 0;
}