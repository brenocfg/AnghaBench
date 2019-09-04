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
typedef  enum mic_hw_family { ____Placeholder_mic_hw_family } mic_hw_family ;

/* Variables and functions */
 int MIC_FAMILY_UNKNOWN ; 
 int MIC_FAMILY_X100 ; 
#define  MIC_X100_PCI_DEVICE_2250 142 
#define  MIC_X100_PCI_DEVICE_2251 141 
#define  MIC_X100_PCI_DEVICE_2252 140 
#define  MIC_X100_PCI_DEVICE_2253 139 
#define  MIC_X100_PCI_DEVICE_2254 138 
#define  MIC_X100_PCI_DEVICE_2255 137 
#define  MIC_X100_PCI_DEVICE_2256 136 
#define  MIC_X100_PCI_DEVICE_2257 135 
#define  MIC_X100_PCI_DEVICE_2258 134 
#define  MIC_X100_PCI_DEVICE_2259 133 
#define  MIC_X100_PCI_DEVICE_225a 132 
#define  MIC_X100_PCI_DEVICE_225b 131 
#define  MIC_X100_PCI_DEVICE_225c 130 
#define  MIC_X100_PCI_DEVICE_225d 129 
#define  MIC_X100_PCI_DEVICE_225e 128 

__attribute__((used)) static enum mic_hw_family mic_get_family(struct pci_dev *pdev)
{
	enum mic_hw_family family;

	switch (pdev->device) {
	case MIC_X100_PCI_DEVICE_2250:
	case MIC_X100_PCI_DEVICE_2251:
	case MIC_X100_PCI_DEVICE_2252:
	case MIC_X100_PCI_DEVICE_2253:
	case MIC_X100_PCI_DEVICE_2254:
	case MIC_X100_PCI_DEVICE_2255:
	case MIC_X100_PCI_DEVICE_2256:
	case MIC_X100_PCI_DEVICE_2257:
	case MIC_X100_PCI_DEVICE_2258:
	case MIC_X100_PCI_DEVICE_2259:
	case MIC_X100_PCI_DEVICE_225a:
	case MIC_X100_PCI_DEVICE_225b:
	case MIC_X100_PCI_DEVICE_225c:
	case MIC_X100_PCI_DEVICE_225d:
	case MIC_X100_PCI_DEVICE_225e:
		family = MIC_FAMILY_X100;
		break;
	default:
		family = MIC_FAMILY_UNKNOWN;
		break;
	}
	return family;
}