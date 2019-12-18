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
struct be_adapter {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int MEMBAR_CTRL_INT_CTRL_HOSTINTR_MASK ; 
 int /*<<< orphan*/  PCICFG_MEMBAR_CTRL_INT_CTRL_OFFSET ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void be_reg_intr_set(struct be_adapter *adapter, bool enable)
{
	u32 reg, enabled;

	pci_read_config_dword(adapter->pdev, PCICFG_MEMBAR_CTRL_INT_CTRL_OFFSET,
			      &reg);
	enabled = reg & MEMBAR_CTRL_INT_CTRL_HOSTINTR_MASK;

	if (!enabled && enable)
		reg |= MEMBAR_CTRL_INT_CTRL_HOSTINTR_MASK;
	else if (enabled && !enable)
		reg &= ~MEMBAR_CTRL_INT_CTRL_HOSTINTR_MASK;
	else
		return;

	pci_write_config_dword(adapter->pdev,
			       PCICFG_MEMBAR_CTRL_INT_CTRL_OFFSET, reg);
}