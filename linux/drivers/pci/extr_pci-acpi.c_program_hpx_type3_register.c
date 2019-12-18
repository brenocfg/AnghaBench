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
typedef  scalar_t__ u16 ;
struct pci_dev {int dummy; } ;
struct hpx_type3 {int device_type; int function_type; int config_space_location; int match_mask_and; int match_value; int reg_mask_and; int reg_mask_or; scalar_t__ reg_offset; scalar_t__ match_offset; int /*<<< orphan*/  pci_exp_cap_ver; int /*<<< orphan*/  pci_exp_cap_id; } ;

/* Variables and functions */
#define  HPX_CFG_DVSEC 132 
#define  HPX_CFG_PCICFG 131 
#define  HPX_CFG_PCIE_CAP 130 
#define  HPX_CFG_PCIE_CAP_EXT 129 
#define  HPX_CFG_VEND_CAP 128 
 int /*<<< orphan*/  PCI_EXT_CAP_VER (int) ; 
 int /*<<< orphan*/  hpx3_cap_ver_matches (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hpx3_device_type (struct pci_dev*) ; 
 int hpx3_function_type (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_dbg (struct pci_dev*,char*,scalar_t__,int,int) ; 
 scalar_t__ pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_warn (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,int) ; 

__attribute__((used)) static void program_hpx_type3_register(struct pci_dev *dev,
				       const struct hpx_type3 *reg)
{
	u32 match_reg, write_reg, header, orig_value;
	u16 pos;

	if (!(hpx3_device_type(dev) & reg->device_type))
		return;

	if (!(hpx3_function_type(dev) & reg->function_type))
		return;

	switch (reg->config_space_location) {
	case HPX_CFG_PCICFG:
		pos = 0;
		break;
	case HPX_CFG_PCIE_CAP:
		pos = pci_find_capability(dev, reg->pci_exp_cap_id);
		if (pos == 0)
			return;

		break;
	case HPX_CFG_PCIE_CAP_EXT:
		pos = pci_find_ext_capability(dev, reg->pci_exp_cap_id);
		if (pos == 0)
			return;

		pci_read_config_dword(dev, pos, &header);
		if (!hpx3_cap_ver_matches(PCI_EXT_CAP_VER(header),
					  reg->pci_exp_cap_ver))
			return;

		break;
	case HPX_CFG_VEND_CAP:	/* Fall through */
	case HPX_CFG_DVSEC:	/* Fall through */
	default:
		pci_warn(dev, "Encountered _HPX type 3 with unsupported config space location");
		return;
	}

	pci_read_config_dword(dev, pos + reg->match_offset, &match_reg);

	if ((match_reg & reg->match_mask_and) != reg->match_value)
		return;

	pci_read_config_dword(dev, pos + reg->reg_offset, &write_reg);
	orig_value = write_reg;
	write_reg &= reg->reg_mask_and;
	write_reg |= reg->reg_mask_or;

	if (orig_value == write_reg)
		return;

	pci_write_config_dword(dev, pos + reg->reg_offset, write_reg);

	pci_dbg(dev, "Applied _HPX3 at [0x%x]: 0x%08x -> 0x%08x",
		pos, orig_value, write_reg);
}