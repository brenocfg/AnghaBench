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
struct pci_dev {scalar_t__ class; } ;

/* Variables and functions */
 scalar_t__ PCI_CLASS_DISPLAY_VGA ; 

__attribute__((used)) static bool is_vga(struct pci_dev *pdev)
{
	return pdev->class == PCI_CLASS_DISPLAY_VGA << 8;
}