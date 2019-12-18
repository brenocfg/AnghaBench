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
typedef  int u8 ;
typedef  int u32 ;
struct pci_dev {scalar_t__ device; int multifunction; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ PCI_DEVICE_ID_NVIDIA_GEFORCE_320M ; 
 int /*<<< orphan*/  PCI_HEADER_TYPE ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int) ; 

__attribute__((used)) static void quirk_nvidia_hda(struct pci_dev *gpu)
{
	u8 hdr_type;
	u32 val;

	/* There was no integrated HDA controller before MCP89 */
	if (gpu->device < PCI_DEVICE_ID_NVIDIA_GEFORCE_320M)
		return;

	/* Bit 25 at offset 0x488 enables the HDA controller */
	pci_read_config_dword(gpu, 0x488, &val);
	if (val & BIT(25))
		return;

	pci_info(gpu, "Enabling HDA controller\n");
	pci_write_config_dword(gpu, 0x488, val | BIT(25));

	/* The GPU becomes a multi-function device when the HDA is enabled */
	pci_read_config_byte(gpu, PCI_HEADER_TYPE, &hdr_type);
	gpu->multifunction = !!(hdr_type & 0x80);
}