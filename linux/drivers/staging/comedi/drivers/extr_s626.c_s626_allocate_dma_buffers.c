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
struct TYPE_3__ {void* physical_base; void* logical_base; } ;
struct TYPE_4__ {void* physical_base; void* logical_base; } ;
struct s626_private {TYPE_1__ rps_buf; TYPE_2__ ana_buf; } ;
struct pci_dev {int dummy; } ;
struct comedi_device {struct s626_private* private; } ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  S626_DMABUF_SIZE ; 
 struct pci_dev* comedi_to_pci_dev (struct comedi_device*) ; 
 void* pci_alloc_consistent (struct pci_dev*,int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static int s626_allocate_dma_buffers(struct comedi_device *dev)
{
	struct pci_dev *pcidev = comedi_to_pci_dev(dev);
	struct s626_private *devpriv = dev->private;
	void *addr;
	dma_addr_t appdma;

	addr = pci_alloc_consistent(pcidev, S626_DMABUF_SIZE, &appdma);
	if (!addr)
		return -ENOMEM;
	devpriv->ana_buf.logical_base = addr;
	devpriv->ana_buf.physical_base = appdma;

	addr = pci_alloc_consistent(pcidev, S626_DMABUF_SIZE, &appdma);
	if (!addr)
		return -ENOMEM;
	devpriv->rps_buf.logical_base = addr;
	devpriv->rps_buf.physical_base = appdma;

	return 0;
}