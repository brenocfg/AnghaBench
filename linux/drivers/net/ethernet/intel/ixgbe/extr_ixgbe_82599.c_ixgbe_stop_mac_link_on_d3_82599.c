#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* read ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {int /*<<< orphan*/  wol_enabled; TYPE_2__ eeprom; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_AUTOC2 ; 
 int /*<<< orphan*/  IXGBE_AUTOC2_LINK_DISABLE_ON_D3_MASK ; 
 int IXGBE_EEPROM_CCD_BIT ; 
 int /*<<< orphan*/  IXGBE_EEPROM_CTRL_2 ; 
 int /*<<< orphan*/  IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_mng_present (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void ixgbe_stop_mac_link_on_d3_82599(struct ixgbe_hw *hw)
{
	u32 autoc2_reg;
	u16 ee_ctrl_2 = 0;

	hw->eeprom.ops.read(hw, IXGBE_EEPROM_CTRL_2, &ee_ctrl_2);

	if (!ixgbe_mng_present(hw) && !hw->wol_enabled &&
	    ee_ctrl_2 & IXGBE_EEPROM_CCD_BIT) {
		autoc2_reg = IXGBE_READ_REG(hw, IXGBE_AUTOC2);
		autoc2_reg |= IXGBE_AUTOC2_LINK_DISABLE_ON_D3_MASK;
		IXGBE_WRITE_REG(hw, IXGBE_AUTOC2, autoc2_reg);
	}
}