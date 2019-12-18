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
typedef  int u16 ;
struct TYPE_2__ {int word_page_size; } ;
struct ixgbe_hw {TYPE_1__ eeprom; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int IXGBE_EEPROM_PAGE_SIZE_MAX ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*,int) ; 
 scalar_t__ ixgbe_read_eeprom_buffer_bit_bang (struct ixgbe_hw*,int,int,int*) ; 
 scalar_t__ ixgbe_write_eeprom_buffer_bit_bang (struct ixgbe_hw*,int,int,int*) ; 

__attribute__((used)) static s32 ixgbe_detect_eeprom_page_size_generic(struct ixgbe_hw *hw,
						 u16 offset)
{
	u16 data[IXGBE_EEPROM_PAGE_SIZE_MAX];
	s32 status;
	u16 i;

	for (i = 0; i < IXGBE_EEPROM_PAGE_SIZE_MAX; i++)
		data[i] = i;

	hw->eeprom.word_page_size = IXGBE_EEPROM_PAGE_SIZE_MAX;
	status = ixgbe_write_eeprom_buffer_bit_bang(hw, offset,
					     IXGBE_EEPROM_PAGE_SIZE_MAX, data);
	hw->eeprom.word_page_size = 0;
	if (status)
		return status;

	status = ixgbe_read_eeprom_buffer_bit_bang(hw, offset, 1, data);
	if (status)
		return status;

	/*
	 * When writing in burst more than the actual page size
	 * EEPROM address wraps around current page.
	 */
	hw->eeprom.word_page_size = IXGBE_EEPROM_PAGE_SIZE_MAX - data[0];

	hw_dbg(hw, "Detected EEPROM page size = %d words.\n",
	       hw->eeprom.word_page_size);
	return 0;
}