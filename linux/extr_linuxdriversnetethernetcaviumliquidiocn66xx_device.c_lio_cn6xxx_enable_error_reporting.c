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
struct octeon_device {TYPE_1__* pci_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN6XXX_PCIE_DEVCTL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pci_read_config_dword (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void lio_cn6xxx_enable_error_reporting(struct octeon_device *oct)
{
	u32 val;

	pci_read_config_dword(oct->pci_dev, CN6XXX_PCIE_DEVCTL, &val);
	if (val & 0x000c0000) {
		dev_err(&oct->pci_dev->dev, "PCI-E Link error detected: 0x%08x\n",
			val & 0x000c0000);
	}

	val |= 0xf;          /* Enable Link error reporting */

	dev_dbg(&oct->pci_dev->dev, "Enabling PCI-E error reporting..\n");
	pci_write_config_dword(oct->pci_dev, CN6XXX_PCIE_DEVCTL, val);
}