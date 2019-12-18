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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int ADDRESS_MSK ; 
 int /*<<< orphan*/  EEPROM_LINK_CALIBRATION ; 
 int /*<<< orphan*/  EEPROM_LINK_GENERAL ; 
 int /*<<< orphan*/  EEPROM_LINK_HOST ; 
 int /*<<< orphan*/  EEPROM_LINK_OTHERS ; 
 int /*<<< orphan*/  EEPROM_LINK_PROCESS_ADJST ; 
 int /*<<< orphan*/  EEPROM_LINK_REGULATORY ; 
 int /*<<< orphan*/  EEPROM_LINK_TXP_LIMIT ; 
 int /*<<< orphan*/  EEPROM_LINK_TXP_LIMIT_SIZE ; 
 int INDIRECT_ADDRESS ; 
#define  INDIRECT_CALIBRATION 135 
#define  INDIRECT_GENERAL 134 
#define  INDIRECT_HOST 133 
#define  INDIRECT_OTHERS 132 
#define  INDIRECT_PROCESS_ADJST 131 
#define  INDIRECT_REGULATORY 130 
#define  INDIRECT_TXP_LIMIT 129 
#define  INDIRECT_TXP_LIMIT_SIZE 128 
 int INDIRECT_TYPE_MSK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int iwl_eeprom_query16 (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 eeprom_indirect_address(const u8 *eeprom, size_t eeprom_size,
				   u32 address)
{
	u16 offset = 0;

	if ((address & INDIRECT_ADDRESS) == 0)
		return address;

	switch (address & INDIRECT_TYPE_MSK) {
	case INDIRECT_HOST:
		offset = iwl_eeprom_query16(eeprom, eeprom_size,
					    EEPROM_LINK_HOST);
		break;
	case INDIRECT_GENERAL:
		offset = iwl_eeprom_query16(eeprom, eeprom_size,
					    EEPROM_LINK_GENERAL);
		break;
	case INDIRECT_REGULATORY:
		offset = iwl_eeprom_query16(eeprom, eeprom_size,
					    EEPROM_LINK_REGULATORY);
		break;
	case INDIRECT_TXP_LIMIT:
		offset = iwl_eeprom_query16(eeprom, eeprom_size,
					    EEPROM_LINK_TXP_LIMIT);
		break;
	case INDIRECT_TXP_LIMIT_SIZE:
		offset = iwl_eeprom_query16(eeprom, eeprom_size,
					    EEPROM_LINK_TXP_LIMIT_SIZE);
		break;
	case INDIRECT_CALIBRATION:
		offset = iwl_eeprom_query16(eeprom, eeprom_size,
					    EEPROM_LINK_CALIBRATION);
		break;
	case INDIRECT_PROCESS_ADJST:
		offset = iwl_eeprom_query16(eeprom, eeprom_size,
					    EEPROM_LINK_PROCESS_ADJST);
		break;
	case INDIRECT_OTHERS:
		offset = iwl_eeprom_query16(eeprom, eeprom_size,
					    EEPROM_LINK_OTHERS);
		break;
	default:
		WARN_ON(1);
		break;
	}

	/* translate the offset from words to byte */
	return (address & ADDRESS_MSK) + (offset << 1);
}