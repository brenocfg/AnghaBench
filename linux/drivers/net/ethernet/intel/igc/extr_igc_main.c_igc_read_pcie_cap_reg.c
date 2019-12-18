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
struct igc_hw {struct igc_adapter* back; } ;
struct igc_adapter {int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_ERR_CONFIG ; 
 int /*<<< orphan*/  IGC_SUCCESS ; 
 int /*<<< orphan*/  pci_is_pcie (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_capability_read_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

s32 igc_read_pcie_cap_reg(struct igc_hw *hw, u32 reg, u16 *value)
{
	struct igc_adapter *adapter = hw->back;

	if (!pci_is_pcie(adapter->pdev))
		return -IGC_ERR_CONFIG;

	pcie_capability_read_word(adapter->pdev, reg, value);

	return IGC_SUCCESS;
}