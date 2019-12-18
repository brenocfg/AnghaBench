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
struct pci_dev {scalar_t__ vendor; int device; } ;
typedef  enum vga_switcheroo_client_id { ____Placeholder_vga_switcheroo_client_id } vga_switcheroo_client_id ;

/* Variables and functions */
 scalar_t__ PCI_VENDOR_ID_INTEL ; 
 scalar_t__ PCI_VENDOR_ID_NVIDIA ; 
 int VGA_SWITCHEROO_DIS ; 
 int VGA_SWITCHEROO_IGD ; 

__attribute__((used)) static enum vga_switcheroo_client_id gmux_get_client_id(struct pci_dev *pdev)
{
	/*
	 * Early Macbook Pros with switchable graphics use nvidia
	 * integrated graphics. Hardcode that the 9400M is integrated.
	 */
	if (pdev->vendor == PCI_VENDOR_ID_INTEL)
		return VGA_SWITCHEROO_IGD;
	else if (pdev->vendor == PCI_VENDOR_ID_NVIDIA &&
		 pdev->device == 0x0863)
		return VGA_SWITCHEROO_IGD;
	else
		return VGA_SWITCHEROO_DIS;
}