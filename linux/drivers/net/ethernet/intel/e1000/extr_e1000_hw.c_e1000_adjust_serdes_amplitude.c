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
typedef  int /*<<< orphan*/  u16 ;
struct e1000_hw {scalar_t__ media_type; int mac_type; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  EEPROM_RESERVED_WORD ; 
 int /*<<< orphan*/  EEPROM_SERDES_AMPLITUDE ; 
 int /*<<< orphan*/  EEPROM_SERDES_AMPLITUDE_MASK ; 
 int /*<<< orphan*/  M88E1000_PHY_EXT_CTRL ; 
#define  e1000_82545_rev_3 129 
#define  e1000_82546_rev_3 128 
 scalar_t__ e1000_media_type_internal_serdes ; 
 scalar_t__ e1000_read_eeprom (struct e1000_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ e1000_write_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 e1000_adjust_serdes_amplitude(struct e1000_hw *hw)
{
	u16 eeprom_data;
	s32 ret_val;

	if (hw->media_type != e1000_media_type_internal_serdes)
		return E1000_SUCCESS;

	switch (hw->mac_type) {
	case e1000_82545_rev_3:
	case e1000_82546_rev_3:
		break;
	default:
		return E1000_SUCCESS;
	}

	ret_val = e1000_read_eeprom(hw, EEPROM_SERDES_AMPLITUDE, 1,
				    &eeprom_data);
	if (ret_val)
		return ret_val;

	if (eeprom_data != EEPROM_RESERVED_WORD) {
		/* Adjust SERDES output amplitude only. */
		eeprom_data &= EEPROM_SERDES_AMPLITUDE_MASK;
		ret_val =
		    e1000_write_phy_reg(hw, M88E1000_PHY_EXT_CTRL, eeprom_data);
		if (ret_val)
			return ret_val;
	}

	return E1000_SUCCESS;
}