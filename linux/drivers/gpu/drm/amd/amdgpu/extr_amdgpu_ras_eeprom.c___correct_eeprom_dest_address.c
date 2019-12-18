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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int EEPROM_ADDR_MSB_MASK ; 
 int EEPROM_RECORD_START ; 
 int EEPROM_SIZE_BYTES ; 
 int EEPROM_TABLE_RECORD_SIZE ; 

__attribute__((used)) static uint32_t __correct_eeprom_dest_address(uint32_t curr_address)
{
	uint32_t next_address = curr_address + EEPROM_TABLE_RECORD_SIZE;

	/* When all EEPROM memory used jump back to 0 address */
	if (next_address > EEPROM_SIZE_BYTES) {
		DRM_INFO("Reached end of EEPROM memory, jumping to 0 "
			 "and overriding old record");
		return EEPROM_RECORD_START;
	}

	/*
	 * To check if we overflow page boundary  compare next address with
	 * current and see if bits 17/8 of the EEPROM address will change
	 * If they do start from the next 256b page
	 *
	 * https://www.st.com/resource/en/datasheet/m24m02-dr.pdf sec. 5.1.2
	 */
	if ((curr_address & EEPROM_ADDR_MSB_MASK) != (next_address & EEPROM_ADDR_MSB_MASK)) {
		DRM_DEBUG_DRIVER("Reached end of EEPROM memory page, jumping to next: %lx",
				(next_address & EEPROM_ADDR_MSB_MASK));

		return  (next_address & EEPROM_ADDR_MSB_MASK);
	}

	return curr_address;
}