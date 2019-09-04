#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_CCMCTL ; 
 int /*<<< orphan*/  E1000_GIOCTL ; 
 int /*<<< orphan*/  E1000_SCCTL ; 
 int /*<<< orphan*/  E1000_SCTL ; 
 scalar_t__ e1000_82575 ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 int /*<<< orphan*/  igb_write_8bit_ctrl_reg (struct e1000_hw*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static s32 igb_reset_init_script_82575(struct e1000_hw *hw)
{
	if (hw->mac.type == e1000_82575) {
		hw_dbg("Running reset init script for 82575\n");
		/* SerDes configuration via SERDESCTRL */
		igb_write_8bit_ctrl_reg(hw, E1000_SCTL, 0x00, 0x0C);
		igb_write_8bit_ctrl_reg(hw, E1000_SCTL, 0x01, 0x78);
		igb_write_8bit_ctrl_reg(hw, E1000_SCTL, 0x1B, 0x23);
		igb_write_8bit_ctrl_reg(hw, E1000_SCTL, 0x23, 0x15);

		/* CCM configuration via CCMCTL register */
		igb_write_8bit_ctrl_reg(hw, E1000_CCMCTL, 0x14, 0x00);
		igb_write_8bit_ctrl_reg(hw, E1000_CCMCTL, 0x10, 0x00);

		/* PCIe lanes configuration */
		igb_write_8bit_ctrl_reg(hw, E1000_GIOCTL, 0x00, 0xEC);
		igb_write_8bit_ctrl_reg(hw, E1000_GIOCTL, 0x61, 0xDF);
		igb_write_8bit_ctrl_reg(hw, E1000_GIOCTL, 0x34, 0x05);
		igb_write_8bit_ctrl_reg(hw, E1000_GIOCTL, 0x2F, 0x81);

		/* PCIe PLL Configuration */
		igb_write_8bit_ctrl_reg(hw, E1000_SCCTL, 0x02, 0x47);
		igb_write_8bit_ctrl_reg(hw, E1000_SCCTL, 0x14, 0x00);
		igb_write_8bit_ctrl_reg(hw, E1000_SCCTL, 0x10, 0x00);
	}

	return 0;
}