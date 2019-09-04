#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct octeon_device {TYPE_1__* pci_dev; int /*<<< orphan*/  octeon_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN23XX_CONFIG_PCIE_CORRECT_ERR_STATUS ; 
 int /*<<< orphan*/  CN23XX_CONFIG_PCIE_DEVCTL ; 
 int CN23XX_CONFIG_PCIE_DEVCTL_MASK ; 
 int /*<<< orphan*/  CN23XX_CONFIG_PCIE_UNCORRECT_ERR_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int /*<<< orphan*/  pci_read_config_dword (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cn23xx_enable_error_reporting(struct octeon_device *oct)
{
	u32 regval;
	u32 uncorrectable_err_mask, corrtable_err_status;

	pci_read_config_dword(oct->pci_dev, CN23XX_CONFIG_PCIE_DEVCTL, &regval);
	if (regval & CN23XX_CONFIG_PCIE_DEVCTL_MASK) {
		uncorrectable_err_mask = 0;
		corrtable_err_status = 0;
		pci_read_config_dword(oct->pci_dev,
				      CN23XX_CONFIG_PCIE_UNCORRECT_ERR_MASK,
				      &uncorrectable_err_mask);
		pci_read_config_dword(oct->pci_dev,
				      CN23XX_CONFIG_PCIE_CORRECT_ERR_STATUS,
				      &corrtable_err_status);
		dev_err(&oct->pci_dev->dev, "PCI-E Fatal error detected;\n"
				 "\tdev_ctl_status_reg = 0x%08x\n"
				 "\tuncorrectable_error_mask_reg = 0x%08x\n"
				 "\tcorrectable_error_status_reg = 0x%08x\n",
			    regval, uncorrectable_err_mask,
			    corrtable_err_status);
	}

	regval |= 0xf; /* Enable Link error reporting */

	dev_dbg(&oct->pci_dev->dev, "OCTEON[%d]: Enabling PCI-E error reporting..\n",
		oct->octeon_id);
	pci_write_config_dword(oct->pci_dev, CN23XX_CONFIG_PCIE_DEVCTL, regval);
}