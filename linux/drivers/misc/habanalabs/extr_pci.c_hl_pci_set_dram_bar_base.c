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
typedef  int u64 ;
typedef  int u32 ;
struct asic_fixed_properties {scalar_t__ pcie_aux_dbi_reg_addr; } ;
struct hl_device {int /*<<< orphan*/  dev; struct asic_fixed_properties asic_prop; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int hl_pci_elbi_write (struct hl_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int hl_pci_iatu_write (struct hl_device*,int,int) ; 
 int lower_32_bits (int) ; 
 int upper_32_bits (int) ; 

int hl_pci_set_dram_bar_base(struct hl_device *hdev, u8 inbound_region, u8 bar,
				u64 addr)
{
	struct asic_fixed_properties *prop = &hdev->asic_prop;
	u32 offset;
	int rc;

	switch (inbound_region) {
	case 0:
		offset = 0x100;
		break;
	case 1:
		offset = 0x300;
		break;
	case 2:
		offset = 0x500;
		break;
	default:
		dev_err(hdev->dev, "Invalid inbound region %d\n",
			inbound_region);
		return -EINVAL;
	}

	if (bar != 0 && bar != 2 && bar != 4) {
		dev_err(hdev->dev, "Invalid PCI BAR %d\n", bar);
		return -EINVAL;
	}

	/* Point to the specified address */
	rc = hl_pci_iatu_write(hdev, offset + 0x14, lower_32_bits(addr));
	rc |= hl_pci_iatu_write(hdev, offset + 0x18, upper_32_bits(addr));
	rc |= hl_pci_iatu_write(hdev, offset + 0x0, 0);
	/* Enable + BAR match + match enable + BAR number */
	rc |= hl_pci_iatu_write(hdev, offset + 0x4, 0xC0080000 | (bar << 8));

	/* Return the DBI window to the default location */
	rc |= hl_pci_elbi_write(hdev, prop->pcie_aux_dbi_reg_addr, 0);
	rc |= hl_pci_elbi_write(hdev, prop->pcie_aux_dbi_reg_addr + 4, 0);

	if (rc)
		dev_err(hdev->dev, "failed to map DRAM bar to 0x%08llx\n",
			addr);

	return rc;
}