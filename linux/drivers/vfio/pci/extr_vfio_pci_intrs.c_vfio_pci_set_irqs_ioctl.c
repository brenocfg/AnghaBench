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
typedef  int uint32_t ;
struct vfio_pci_device {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int ENOTTY ; 
#define  VFIO_IRQ_SET_ACTION_MASK 135 
#define  VFIO_IRQ_SET_ACTION_TRIGGER 134 
 int VFIO_IRQ_SET_ACTION_TYPE_MASK ; 
#define  VFIO_IRQ_SET_ACTION_UNMASK 133 
#define  VFIO_PCI_ERR_IRQ_INDEX 132 
#define  VFIO_PCI_INTX_IRQ_INDEX 131 
#define  VFIO_PCI_MSIX_IRQ_INDEX 130 
#define  VFIO_PCI_MSI_IRQ_INDEX 129 
#define  VFIO_PCI_REQ_IRQ_INDEX 128 
 int /*<<< orphan*/  pci_is_pcie (int /*<<< orphan*/ ) ; 
 int vfio_pci_set_err_trigger (struct vfio_pci_device*,unsigned int,unsigned int,unsigned int,int,void*) ; 
 int vfio_pci_set_intx_mask (struct vfio_pci_device*,unsigned int,unsigned int,unsigned int,int,void*) ; 
 int vfio_pci_set_intx_trigger (struct vfio_pci_device*,unsigned int,unsigned int,unsigned int,int,void*) ; 
 int vfio_pci_set_intx_unmask (struct vfio_pci_device*,unsigned int,unsigned int,unsigned int,int,void*) ; 
 int vfio_pci_set_msi_trigger (struct vfio_pci_device*,unsigned int,unsigned int,unsigned int,int,void*) ; 
 int vfio_pci_set_req_trigger (struct vfio_pci_device*,unsigned int,unsigned int,unsigned int,int,void*) ; 

int vfio_pci_set_irqs_ioctl(struct vfio_pci_device *vdev, uint32_t flags,
			    unsigned index, unsigned start, unsigned count,
			    void *data)
{
	int (*func)(struct vfio_pci_device *vdev, unsigned index,
		    unsigned start, unsigned count, uint32_t flags,
		    void *data) = NULL;

	switch (index) {
	case VFIO_PCI_INTX_IRQ_INDEX:
		switch (flags & VFIO_IRQ_SET_ACTION_TYPE_MASK) {
		case VFIO_IRQ_SET_ACTION_MASK:
			func = vfio_pci_set_intx_mask;
			break;
		case VFIO_IRQ_SET_ACTION_UNMASK:
			func = vfio_pci_set_intx_unmask;
			break;
		case VFIO_IRQ_SET_ACTION_TRIGGER:
			func = vfio_pci_set_intx_trigger;
			break;
		}
		break;
	case VFIO_PCI_MSI_IRQ_INDEX:
	case VFIO_PCI_MSIX_IRQ_INDEX:
		switch (flags & VFIO_IRQ_SET_ACTION_TYPE_MASK) {
		case VFIO_IRQ_SET_ACTION_MASK:
		case VFIO_IRQ_SET_ACTION_UNMASK:
			/* XXX Need masking support exported */
			break;
		case VFIO_IRQ_SET_ACTION_TRIGGER:
			func = vfio_pci_set_msi_trigger;
			break;
		}
		break;
	case VFIO_PCI_ERR_IRQ_INDEX:
		switch (flags & VFIO_IRQ_SET_ACTION_TYPE_MASK) {
		case VFIO_IRQ_SET_ACTION_TRIGGER:
			if (pci_is_pcie(vdev->pdev))
				func = vfio_pci_set_err_trigger;
			break;
		}
		break;
	case VFIO_PCI_REQ_IRQ_INDEX:
		switch (flags & VFIO_IRQ_SET_ACTION_TYPE_MASK) {
		case VFIO_IRQ_SET_ACTION_TRIGGER:
			func = vfio_pci_set_req_trigger;
			break;
		}
		break;
	}

	if (!func)
		return -ENOTTY;

	return func(vdev, index, start, count, flags, data);
}