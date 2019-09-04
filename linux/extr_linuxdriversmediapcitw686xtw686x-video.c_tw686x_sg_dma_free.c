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
struct tw686x_video_channel {int /*<<< orphan*/ ** sg_descs; struct tw686x_dev* dev; struct tw686x_dma_desc* dma_descs; } ;
struct tw686x_dma_desc {int /*<<< orphan*/ * virt; int /*<<< orphan*/  phys; scalar_t__ size; } ;
struct tw686x_dev {int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tw686x_sg_dma_free(struct tw686x_video_channel *vc,
			       unsigned int pb)
{
	struct tw686x_dma_desc *desc = &vc->dma_descs[pb];
	struct tw686x_dev *dev = vc->dev;

	if (desc->size) {
		pci_free_consistent(dev->pci_dev, desc->size,
				    desc->virt, desc->phys);
		desc->virt = NULL;
	}

	vc->sg_descs[pb] = NULL;
}