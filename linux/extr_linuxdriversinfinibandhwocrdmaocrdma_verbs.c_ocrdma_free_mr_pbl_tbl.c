#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ocrdma_hw_mr {int num_pbls; TYPE_2__* pbl_table; int /*<<< orphan*/  pbl_size; } ;
struct TYPE_3__ {struct pci_dev* pdev; } ;
struct ocrdma_dev {TYPE_1__ nic_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  pa; int /*<<< orphan*/  va; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 

__attribute__((used)) static void ocrdma_free_mr_pbl_tbl(struct ocrdma_dev *dev,
				   struct ocrdma_hw_mr *mr)
{
	struct pci_dev *pdev = dev->nic_info.pdev;
	int i = 0;

	if (mr->pbl_table) {
		for (i = 0; i < mr->num_pbls; i++) {
			if (!mr->pbl_table[i].va)
				continue;
			dma_free_coherent(&pdev->dev, mr->pbl_size,
					  mr->pbl_table[i].va,
					  mr->pbl_table[i].pa);
		}
		kfree(mr->pbl_table);
		mr->pbl_table = NULL;
	}
}