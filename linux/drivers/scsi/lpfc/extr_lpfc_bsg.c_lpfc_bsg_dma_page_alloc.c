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
struct lpfc_hba {struct pci_dev* pcidev; } ;
struct lpfc_dmabuf {int /*<<< orphan*/  virt; int /*<<< orphan*/  phys; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSG_MBOX_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct lpfc_dmabuf*) ; 
 struct lpfc_dmabuf* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct lpfc_dmabuf *
lpfc_bsg_dma_page_alloc(struct lpfc_hba *phba)
{
	struct lpfc_dmabuf *dmabuf;
	struct pci_dev *pcidev = phba->pcidev;

	/* allocate dma buffer struct */
	dmabuf = kmalloc(sizeof(struct lpfc_dmabuf), GFP_KERNEL);
	if (!dmabuf)
		return NULL;

	INIT_LIST_HEAD(&dmabuf->list);

	/* now, allocate dma buffer */
	dmabuf->virt = dma_alloc_coherent(&pcidev->dev, BSG_MBOX_SIZE,
					  &(dmabuf->phys), GFP_KERNEL);

	if (!dmabuf->virt) {
		kfree(dmabuf);
		return NULL;
	}

	return dmabuf;
}