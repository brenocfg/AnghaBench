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
struct pci_dev {scalar_t__ vendor; scalar_t__ device; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_ID_INTERG_2000 ; 
 scalar_t__ PCI_DEVICE_ID_INTERG_2010 ; 
 scalar_t__ PCI_DEVICE_ID_ITE_8152 ; 
 scalar_t__ PCI_VENDOR_ID_INTERG ; 
 scalar_t__ PCI_VENDOR_ID_ITE ; 

__attribute__((used)) static inline int pdev_bad_for_parity(struct pci_dev *dev)
{
	return ((dev->vendor == PCI_VENDOR_ID_INTERG &&
		 (dev->device == PCI_DEVICE_ID_INTERG_2000 ||
		  dev->device == PCI_DEVICE_ID_INTERG_2010)) ||
		(dev->vendor == PCI_VENDOR_ID_ITE &&
		 dev->device == PCI_DEVICE_ID_ITE_8152));

}