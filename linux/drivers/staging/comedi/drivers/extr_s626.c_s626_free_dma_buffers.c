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
struct TYPE_4__ {int /*<<< orphan*/  physical_base; scalar_t__ logical_base; } ;
struct TYPE_3__ {int /*<<< orphan*/  physical_base; scalar_t__ logical_base; } ;
struct s626_private {TYPE_2__ ana_buf; TYPE_1__ rps_buf; } ;
struct pci_dev {int dummy; } ;
struct comedi_device {struct s626_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  S626_DMABUF_SIZE ; 
 struct pci_dev* comedi_to_pci_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s626_free_dma_buffers(struct comedi_device *dev)
{
	struct pci_dev *pcidev = comedi_to_pci_dev(dev);
	struct s626_private *devpriv = dev->private;

	if (!devpriv)
		return;

	if (devpriv->rps_buf.logical_base)
		pci_free_consistent(pcidev, S626_DMABUF_SIZE,
				    devpriv->rps_buf.logical_base,
				    devpriv->rps_buf.physical_base);
	if (devpriv->ana_buf.logical_base)
		pci_free_consistent(pcidev, S626_DMABUF_SIZE,
				    devpriv->ana_buf.logical_base,
				    devpriv->ana_buf.physical_base);
}