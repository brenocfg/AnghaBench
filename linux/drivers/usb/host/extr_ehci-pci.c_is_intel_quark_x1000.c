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
 scalar_t__ PCI_DEVICE_ID_INTEL_QUARK_X1000_SOC ; 
 scalar_t__ PCI_VENDOR_ID_INTEL ; 

__attribute__((used)) static inline bool is_intel_quark_x1000(struct pci_dev *pdev)
{
	return pdev->vendor == PCI_VENDOR_ID_INTEL &&
		pdev->device == PCI_DEVICE_ID_INTEL_QUARK_X1000_SOC;
}