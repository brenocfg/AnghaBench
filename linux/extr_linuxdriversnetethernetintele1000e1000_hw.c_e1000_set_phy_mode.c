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
typedef  int u16 ;
struct e1000_hw {scalar_t__ mac_type; scalar_t__ media_type; int phy_reset_disable; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_SUCCESS ; 
 int EEPROM_PHY_CLASS_A ; 
 int /*<<< orphan*/  EEPROM_PHY_CLASS_WORD ; 
 int EEPROM_RESERVED_WORD ; 
 int /*<<< orphan*/  M88E1000_PHY_GEN_CONTROL ; 
 int /*<<< orphan*/  M88E1000_PHY_PAGE_SELECT ; 
 scalar_t__ e1000_82545_rev_3 ; 
 scalar_t__ e1000_media_type_copper ; 
 scalar_t__ e1000_read_eeprom (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ e1000_write_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 e1000_set_phy_mode(struct e1000_hw *hw)
{
	s32 ret_val;
	u16 eeprom_data;

	if ((hw->mac_type == e1000_82545_rev_3) &&
	    (hw->media_type == e1000_media_type_copper)) {
		ret_val =
		    e1000_read_eeprom(hw, EEPROM_PHY_CLASS_WORD, 1,
				      &eeprom_data);
		if (ret_val)
			return ret_val;

		if ((eeprom_data != EEPROM_RESERVED_WORD) &&
		    (eeprom_data & EEPROM_PHY_CLASS_A)) {
			ret_val =
			    e1000_write_phy_reg(hw, M88E1000_PHY_PAGE_SELECT,
						0x000B);
			if (ret_val)
				return ret_val;
			ret_val =
			    e1000_write_phy_reg(hw, M88E1000_PHY_GEN_CONTROL,
						0x8104);
			if (ret_val)
				return ret_val;

			hw->phy_reset_disable = false;
		}
	}

	return E1000_SUCCESS;
}