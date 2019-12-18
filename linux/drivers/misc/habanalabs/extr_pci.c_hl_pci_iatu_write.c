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
typedef  int u32 ;
struct asic_fixed_properties {scalar_t__ pcie_dbi_base_address; scalar_t__ pcie_aux_dbi_reg_addr; } ;
struct hl_device {struct asic_fixed_properties asic_prop; } ;

/* Variables and functions */
 int EIO ; 
 int hl_pci_elbi_write (struct hl_device*,scalar_t__,int) ; 

int hl_pci_iatu_write(struct hl_device *hdev, u32 addr, u32 data)
{
	struct asic_fixed_properties *prop = &hdev->asic_prop;
	u32 dbi_offset;
	int rc;

	dbi_offset = addr & 0xFFF;

	rc = hl_pci_elbi_write(hdev, prop->pcie_aux_dbi_reg_addr, 0x00300000);
	rc |= hl_pci_elbi_write(hdev, prop->pcie_dbi_base_address + dbi_offset,
				data);

	if (rc)
		return -EIO;

	return 0;
}