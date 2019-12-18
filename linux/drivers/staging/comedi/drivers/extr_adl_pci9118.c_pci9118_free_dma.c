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
struct pci9118_private {struct pci9118_dmabuf* dmabuf; } ;
struct pci9118_dmabuf {int /*<<< orphan*/  hw; scalar_t__ virt; int /*<<< orphan*/  size; } ;
struct comedi_device {int /*<<< orphan*/  hw_dev; struct pci9118_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pci9118_free_dma(struct comedi_device *dev)
{
	struct pci9118_private *devpriv = dev->private;
	struct pci9118_dmabuf *dmabuf;
	int i;

	if (!devpriv)
		return;

	for (i = 0; i < 2; i++) {
		dmabuf = &devpriv->dmabuf[i];
		if (dmabuf->virt) {
			dma_free_coherent(dev->hw_dev, dmabuf->size,
					  dmabuf->virt, dmabuf->hw);
		}
	}
}