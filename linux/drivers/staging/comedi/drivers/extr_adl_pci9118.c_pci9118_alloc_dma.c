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
struct pci9118_private {int master; int dma_doublebuf; struct pci9118_dmabuf* dmabuf; } ;
struct pci9118_dmabuf {int size; scalar_t__ virt; int /*<<< orphan*/  hw; } ;
struct comedi_device {int /*<<< orphan*/  hw_dev; struct pci9118_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pci9118_alloc_dma(struct comedi_device *dev)
{
	struct pci9118_private *devpriv = dev->private;
	struct pci9118_dmabuf *dmabuf;
	int order;
	int i;

	for (i = 0; i < 2; i++) {
		dmabuf = &devpriv->dmabuf[i];
		for (order = 2; order >= 0; order--) {
			dmabuf->virt =
			    dma_alloc_coherent(dev->hw_dev, PAGE_SIZE << order,
					       &dmabuf->hw, GFP_KERNEL);
			if (dmabuf->virt)
				break;
		}
		if (!dmabuf->virt)
			break;
		dmabuf->size = PAGE_SIZE << order;

		if (i == 0)
			devpriv->master = 1;
		if (i == 1)
			devpriv->dma_doublebuf = 1;
	}
}