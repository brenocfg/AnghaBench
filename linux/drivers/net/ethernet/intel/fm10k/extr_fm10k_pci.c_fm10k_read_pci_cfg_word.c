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
typedef  int u16 ;
struct fm10k_intfc {int /*<<< orphan*/  pdev; } ;
struct fm10k_hw {int /*<<< orphan*/  hw_addr; struct fm10k_intfc* back; } ;

/* Variables and functions */
 scalar_t__ FM10K_REMOVED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_write_flush (struct fm10k_hw*) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

u16 fm10k_read_pci_cfg_word(struct fm10k_hw *hw, u32 reg)
{
	struct fm10k_intfc *interface = hw->back;
	u16 value = 0;

	if (FM10K_REMOVED(hw->hw_addr))
		return ~value;

	pci_read_config_word(interface->pdev, reg, &value);
	if (value == 0xFFFF)
		fm10k_write_flush(hw);

	return value;
}