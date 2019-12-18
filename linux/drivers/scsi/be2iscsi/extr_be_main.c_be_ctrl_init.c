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
struct be_dma_mem {int size; void* va; void* dma; } ;
struct be_ctrl_info {int /*<<< orphan*/  mcc_lock; int /*<<< orphan*/  mbox_lock; struct pci_dev* pdev; struct be_dma_mem mbox_mem; struct be_dma_mem mbox_mem_alloced; } ;
struct beiscsi_hba {struct be_ctrl_info ctrl; } ;
struct be_mcc_mailbox {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* PTR_ALIGN (void*,int) ; 
 int beiscsi_map_pci_bars (struct beiscsi_hba*,struct pci_dev*) ; 
 int /*<<< orphan*/  beiscsi_unmap_pci_function (struct beiscsi_hba*) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int be_ctrl_init(struct beiscsi_hba *phba, struct pci_dev *pdev)
{
	struct be_ctrl_info *ctrl = &phba->ctrl;
	struct be_dma_mem *mbox_mem_alloc = &ctrl->mbox_mem_alloced;
	struct be_dma_mem *mbox_mem_align = &ctrl->mbox_mem;
	int status = 0;

	ctrl->pdev = pdev;
	status = beiscsi_map_pci_bars(phba, pdev);
	if (status)
		return status;
	mbox_mem_alloc->size = sizeof(struct be_mcc_mailbox) + 16;
	mbox_mem_alloc->va = dma_alloc_coherent(&pdev->dev,
			mbox_mem_alloc->size, &mbox_mem_alloc->dma, GFP_KERNEL);
	if (!mbox_mem_alloc->va) {
		beiscsi_unmap_pci_function(phba);
		return -ENOMEM;
	}

	mbox_mem_align->size = sizeof(struct be_mcc_mailbox);
	mbox_mem_align->va = PTR_ALIGN(mbox_mem_alloc->va, 16);
	mbox_mem_align->dma = PTR_ALIGN(mbox_mem_alloc->dma, 16);
	memset(mbox_mem_align->va, 0, sizeof(struct be_mcc_mailbox));
	mutex_init(&ctrl->mbox_lock);
	spin_lock_init(&phba->ctrl.mcc_lock);

	return status;
}