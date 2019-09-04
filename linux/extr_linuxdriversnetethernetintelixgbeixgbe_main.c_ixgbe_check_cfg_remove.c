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
typedef  scalar_t__ u16 ;
struct pci_dev {int dummy; } ;
struct ixgbe_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ IXGBE_FAILED_READ_CFG_WORD ; 
 int /*<<< orphan*/  PCI_VENDOR_ID ; 
 int /*<<< orphan*/  ixgbe_remove_adapter (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static bool ixgbe_check_cfg_remove(struct ixgbe_hw *hw, struct pci_dev *pdev)
{
	u16 value;

	pci_read_config_word(pdev, PCI_VENDOR_ID, &value);
	if (value == IXGBE_FAILED_READ_CFG_WORD) {
		ixgbe_remove_adapter(hw);
		return true;
	}
	return false;
}