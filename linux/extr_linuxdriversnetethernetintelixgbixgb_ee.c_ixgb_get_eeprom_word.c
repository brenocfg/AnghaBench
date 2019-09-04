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
typedef  size_t u16 ;
struct ixgb_hw {int /*<<< orphan*/ * eeprom; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 size_t IXGB_EEPROM_SIZE ; 
 scalar_t__ ixgb_check_and_get_eeprom_data (struct ixgb_hw*) ; 

__le16
ixgb_get_eeprom_word(struct ixgb_hw *hw, u16 index)
{

	if (index < IXGB_EEPROM_SIZE && ixgb_check_and_get_eeprom_data(hw))
		return hw->eeprom[index];

	return 0;
}