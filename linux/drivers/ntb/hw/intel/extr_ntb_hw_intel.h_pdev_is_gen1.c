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
#define  PCI_DEVICE_ID_INTEL_NTB_B2B_BDX 142 
#define  PCI_DEVICE_ID_INTEL_NTB_B2B_HSX 141 
#define  PCI_DEVICE_ID_INTEL_NTB_B2B_IVT 140 
#define  PCI_DEVICE_ID_INTEL_NTB_B2B_JSF 139 
#define  PCI_DEVICE_ID_INTEL_NTB_B2B_SNB 138 
#define  PCI_DEVICE_ID_INTEL_NTB_PS_BDX 137 
#define  PCI_DEVICE_ID_INTEL_NTB_PS_HSX 136 
#define  PCI_DEVICE_ID_INTEL_NTB_PS_IVT 135 
#define  PCI_DEVICE_ID_INTEL_NTB_PS_JSF 134 
#define  PCI_DEVICE_ID_INTEL_NTB_PS_SNB 133 
#define  PCI_DEVICE_ID_INTEL_NTB_SS_BDX 132 
#define  PCI_DEVICE_ID_INTEL_NTB_SS_HSX 131 
#define  PCI_DEVICE_ID_INTEL_NTB_SS_IVT 130 
#define  PCI_DEVICE_ID_INTEL_NTB_SS_JSF 129 
#define  PCI_DEVICE_ID_INTEL_NTB_SS_SNB 128 

__attribute__((used)) static inline int pdev_is_gen1(struct pci_dev *pdev)
{
	switch (pdev->device) {
	case PCI_DEVICE_ID_INTEL_NTB_SS_JSF:
	case PCI_DEVICE_ID_INTEL_NTB_SS_SNB:
	case PCI_DEVICE_ID_INTEL_NTB_SS_IVT:
	case PCI_DEVICE_ID_INTEL_NTB_SS_HSX:
	case PCI_DEVICE_ID_INTEL_NTB_SS_BDX:
	case PCI_DEVICE_ID_INTEL_NTB_PS_JSF:
	case PCI_DEVICE_ID_INTEL_NTB_PS_SNB:
	case PCI_DEVICE_ID_INTEL_NTB_PS_IVT:
	case PCI_DEVICE_ID_INTEL_NTB_PS_HSX:
	case PCI_DEVICE_ID_INTEL_NTB_PS_BDX:
	case PCI_DEVICE_ID_INTEL_NTB_B2B_JSF:
	case PCI_DEVICE_ID_INTEL_NTB_B2B_SNB:
	case PCI_DEVICE_ID_INTEL_NTB_B2B_IVT:
	case PCI_DEVICE_ID_INTEL_NTB_B2B_HSX:
	case PCI_DEVICE_ID_INTEL_NTB_B2B_BDX:
		return 1;
	}
	return 0;
}