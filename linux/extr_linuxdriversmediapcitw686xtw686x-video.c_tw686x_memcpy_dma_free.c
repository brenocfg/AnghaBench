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
struct tw686x_video_channel {struct tw686x_dev* dev; struct tw686x_dma_desc* dma_descs; } ;
struct tw686x_dma_desc {int /*<<< orphan*/ * virt; int /*<<< orphan*/  phys; int /*<<< orphan*/  size; } ;
struct tw686x_dev {struct pci_dev* pci_dev; int /*<<< orphan*/  lock; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void tw686x_memcpy_dma_free(struct tw686x_video_channel *vc,
				   unsigned int pb)
{
	struct tw686x_dma_desc *desc = &vc->dma_descs[pb];
	struct tw686x_dev *dev = vc->dev;
	struct pci_dev *pci_dev;
	unsigned long flags;

	/* Check device presence. Shouldn't really happen! */
	spin_lock_irqsave(&dev->lock, flags);
	pci_dev = dev->pci_dev;
	spin_unlock_irqrestore(&dev->lock, flags);
	if (!pci_dev) {
		WARN(1, "trying to deallocate on missing device\n");
		return;
	}

	if (desc->virt) {
		pci_free_consistent(dev->pci_dev, desc->size,
				    desc->virt, desc->phys);
		desc->virt = NULL;
	}
}