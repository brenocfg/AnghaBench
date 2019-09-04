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
struct qedr_pbl_info {int num_pbls; int /*<<< orphan*/  pbl_size; } ;
struct qedr_pbl {int /*<<< orphan*/  pa; int /*<<< orphan*/  va; } ;
struct qedr_dev {struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qedr_pbl*) ; 

__attribute__((used)) static void qedr_free_pbl(struct qedr_dev *dev,
			  struct qedr_pbl_info *pbl_info, struct qedr_pbl *pbl)
{
	struct pci_dev *pdev = dev->pdev;
	int i;

	for (i = 0; i < pbl_info->num_pbls; i++) {
		if (!pbl[i].va)
			continue;
		dma_free_coherent(&pdev->dev, pbl_info->pbl_size,
				  pbl[i].va, pbl[i].pa);
	}

	kfree(pbl);
}