#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tw686x_dev {int /*<<< orphan*/  pci_dev; } ;
struct tw686x_audio_channel {TYPE_1__* dma_descs; } ;
struct TYPE_2__ {int /*<<< orphan*/ * virt; int /*<<< orphan*/  phys; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tw686x_audio_dma_free(struct tw686x_dev *dev,
				  struct tw686x_audio_channel *ac)
{
	int pb;

	for (pb = 0; pb < 2; pb++) {
		if (!ac->dma_descs[pb].virt)
			continue;
		pci_free_consistent(dev->pci_dev, ac->dma_descs[pb].size,
				    ac->dma_descs[pb].virt,
				    ac->dma_descs[pb].phys);
		ac->dma_descs[pb].virt = NULL;
	}
}