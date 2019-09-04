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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct ixgbe_hw {int /*<<< orphan*/  hw_addr; struct ixgbe_adapter* back; } ;
struct ixgbe_adapter {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ IXGBE_FAILED_READ_CFG_WORD ; 
 scalar_t__ ixgbe_check_cfg_remove (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_removed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

u16 ixgbe_read_pci_cfg_word(struct ixgbe_hw *hw, u32 reg)
{
	struct ixgbe_adapter *adapter = hw->back;
	u16 value;

	if (ixgbe_removed(hw->hw_addr))
		return IXGBE_FAILED_READ_CFG_WORD;
	pci_read_config_word(adapter->pdev, reg, &value);
	if (value == IXGBE_FAILED_READ_CFG_WORD &&
	    ixgbe_check_cfg_remove(hw, adapter->pdev))
		return IXGBE_FAILED_READ_CFG_WORD;
	return value;
}