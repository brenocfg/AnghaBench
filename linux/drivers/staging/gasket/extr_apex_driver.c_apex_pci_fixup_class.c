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
struct pci_dev {int class; } ;

/* Variables and functions */
 int PCI_CLASS_SYSTEM_OTHER ; 

__attribute__((used)) static void apex_pci_fixup_class(struct pci_dev *pdev)
{
	pdev->class = (PCI_CLASS_SYSTEM_OTHER << 8) | pdev->class;
}