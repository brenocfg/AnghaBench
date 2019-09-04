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
struct pci_dev {int device; } ;

/* Variables and functions */
#define  PCI_DEVICE_ID_INTEL_IOAT_IVB0 137 
#define  PCI_DEVICE_ID_INTEL_IOAT_IVB1 136 
#define  PCI_DEVICE_ID_INTEL_IOAT_IVB2 135 
#define  PCI_DEVICE_ID_INTEL_IOAT_IVB3 134 
#define  PCI_DEVICE_ID_INTEL_IOAT_IVB4 133 
#define  PCI_DEVICE_ID_INTEL_IOAT_IVB5 132 
#define  PCI_DEVICE_ID_INTEL_IOAT_IVB6 131 
#define  PCI_DEVICE_ID_INTEL_IOAT_IVB7 130 
#define  PCI_DEVICE_ID_INTEL_IOAT_IVB8 129 
#define  PCI_DEVICE_ID_INTEL_IOAT_IVB9 128 

__attribute__((used)) static bool is_ivb_ioat(struct pci_dev *pdev)
{
	switch (pdev->device) {
	case PCI_DEVICE_ID_INTEL_IOAT_IVB0:
	case PCI_DEVICE_ID_INTEL_IOAT_IVB1:
	case PCI_DEVICE_ID_INTEL_IOAT_IVB2:
	case PCI_DEVICE_ID_INTEL_IOAT_IVB3:
	case PCI_DEVICE_ID_INTEL_IOAT_IVB4:
	case PCI_DEVICE_ID_INTEL_IOAT_IVB5:
	case PCI_DEVICE_ID_INTEL_IOAT_IVB6:
	case PCI_DEVICE_ID_INTEL_IOAT_IVB7:
	case PCI_DEVICE_ID_INTEL_IOAT_IVB8:
	case PCI_DEVICE_ID_INTEL_IOAT_IVB9:
		return true;
	default:
		return false;
	}

}