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
typedef  int /*<<< orphan*/  u16 ;
struct igb_adapter {int /*<<< orphan*/  pdev; } ;
struct e1000_hw {struct igb_adapter* back; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ERR_CONFIG ; 
 scalar_t__ pcie_capability_write_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s32 igb_write_pcie_cap_reg(struct e1000_hw *hw, u32 reg, u16 *value)
{
	struct igb_adapter *adapter = hw->back;

	if (pcie_capability_write_word(adapter->pdev, reg, *value))
		return -E1000_ERR_CONFIG;

	return 0;
}