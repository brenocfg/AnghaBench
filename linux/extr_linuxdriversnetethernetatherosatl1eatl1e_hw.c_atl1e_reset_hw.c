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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct atl1e_hw {struct atl1e_adapter* adapter; } ;
struct atl1e_adapter {int /*<<< orphan*/  netdev; struct pci_dev* pdev; } ;

/* Variables and functions */
 int AT_ERR_TIMEOUT ; 
 int AT_HW_MAX_IDLE_DELAY ; 
 scalar_t__ AT_READ_REG (struct atl1e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT_WRITE_REG (struct atl1e_hw*,int /*<<< orphan*/ ,int) ; 
 int CMD_BUS_MASTER ; 
 int CMD_IO_SPACE ; 
 int CMD_MEMORY_SPACE ; 
 int MASTER_CTRL_LED_MODE ; 
 int MASTER_CTRL_SOFT_RST ; 
 int /*<<< orphan*/  PCI_REG_COMMAND ; 
 int /*<<< orphan*/  REG_IDLE_STATUS ; 
 int /*<<< orphan*/  REG_MASTER_CTRL ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 

int atl1e_reset_hw(struct atl1e_hw *hw)
{
	struct atl1e_adapter *adapter = hw->adapter;
	struct pci_dev *pdev = adapter->pdev;

	u32 idle_status_data = 0;
	u16 pci_cfg_cmd_word = 0;
	int timeout = 0;

	/* Workaround for PCI problem when BIOS sets MMRBC incorrectly. */
	pci_read_config_word(pdev, PCI_REG_COMMAND, &pci_cfg_cmd_word);
	if ((pci_cfg_cmd_word & (CMD_IO_SPACE |
				CMD_MEMORY_SPACE | CMD_BUS_MASTER))
			!= (CMD_IO_SPACE | CMD_MEMORY_SPACE | CMD_BUS_MASTER)) {
		pci_cfg_cmd_word |= (CMD_IO_SPACE |
				     CMD_MEMORY_SPACE | CMD_BUS_MASTER);
		pci_write_config_word(pdev, PCI_REG_COMMAND, pci_cfg_cmd_word);
	}

	/*
	 * Issue Soft Reset to the MAC.  This will reset the chip's
	 * transmit, receive, DMA.  It will not effect
	 * the current PCI configuration.  The global reset bit is self-
	 * clearing, and should clear within a microsecond.
	 */
	AT_WRITE_REG(hw, REG_MASTER_CTRL,
			MASTER_CTRL_LED_MODE | MASTER_CTRL_SOFT_RST);
	wmb();
	msleep(1);

	/* Wait at least 10ms for All module to be Idle */
	for (timeout = 0; timeout < AT_HW_MAX_IDLE_DELAY; timeout++) {
		idle_status_data = AT_READ_REG(hw, REG_IDLE_STATUS);
		if (idle_status_data == 0)
			break;
		msleep(1);
		cpu_relax();
	}

	if (timeout >= AT_HW_MAX_IDLE_DELAY) {
		netdev_err(adapter->netdev,
			   "MAC state machine can't be idle since disabled for 10ms second\n");
		return AT_ERR_TIMEOUT;
	}

	return 0;
}