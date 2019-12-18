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
struct pci_dev {int dummy; } ;
struct alcor_pci_priv {int pdev_cap_off; int parent_cap_off; int pdev_aspm_cap; int ext_config_dev_aspm; struct pci_dev* pdev; struct pci_dev* parent_pdev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ALCOR_PCIE_LINK_CTRL_OFFSET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 

__attribute__((used)) static void alcor_pci_aspm_ctrl(struct alcor_pci_priv *priv, u8 aspm_enable)
{
	struct pci_dev *pci;
	u8 aspm_ctrl, i;
	int where;
	u32 val32;

	if ((!priv->pdev_cap_off) || (!priv->parent_cap_off)) {
		dev_dbg(priv->dev, "pci_cap_off: %x, parent_cap_off: %x\n",
			priv->pdev_cap_off, priv->parent_cap_off);
		return;
	}

	if (!priv->pdev_aspm_cap)
		return;

	aspm_ctrl = 0;
	if (aspm_enable) {
		aspm_ctrl = priv->ext_config_dev_aspm;

		if (!aspm_ctrl) {
			dev_dbg(priv->dev, "aspm_ctrl == 0\n");
			return;
		}
	}

	for (i = 0; i < 2; i++) {

		if (i) {
			pci   = priv->parent_pdev;
			where = priv->parent_cap_off
				+ ALCOR_PCIE_LINK_CTRL_OFFSET;
		} else {
			pci   = priv->pdev;
			where = priv->pdev_cap_off
				+ ALCOR_PCIE_LINK_CTRL_OFFSET;
		}

		pci_read_config_dword(pci, where, &val32);
		val32 &= (~0x03);
		val32 |= (aspm_ctrl & priv->pdev_aspm_cap);
		pci_write_config_byte(pci, where, (u8)val32);
	}

}