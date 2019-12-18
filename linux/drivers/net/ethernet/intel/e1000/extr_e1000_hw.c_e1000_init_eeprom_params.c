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
typedef  int u16 ;
struct e1000_eeprom_info {scalar_t__ type; int word_size; int opcode_bits; int address_bits; int delay_usec; int page_size; } ;
struct e1000_hw {int mac_type; struct e1000_eeprom_info eeprom; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int E1000_EECD_ADDR_BITS ; 
 int E1000_EECD_SIZE ; 
 int E1000_EECD_TYPE ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  EECD ; 
 int /*<<< orphan*/  EEPROM_CFG ; 
 int EEPROM_SIZE_MASK ; 
 int EEPROM_SIZE_SHIFT ; 
 int EEPROM_WORD_SIZE_SHIFT ; 
#define  e1000_82540 140 
#define  e1000_82541 139 
#define  e1000_82541_rev_2 138 
#define  e1000_82542_rev2_0 137 
#define  e1000_82542_rev2_1 136 
#define  e1000_82543 135 
#define  e1000_82544 134 
#define  e1000_82545 133 
#define  e1000_82545_rev_3 132 
#define  e1000_82546 131 
#define  e1000_82546_rev_3 130 
#define  e1000_82547 129 
#define  e1000_82547_rev_2 128 
 void* e1000_eeprom_microwire ; 
 scalar_t__ e1000_eeprom_spi ; 
 scalar_t__ e1000_read_eeprom (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ; 
 int er32 (int /*<<< orphan*/ ) ; 

s32 e1000_init_eeprom_params(struct e1000_hw *hw)
{
	struct e1000_eeprom_info *eeprom = &hw->eeprom;
	u32 eecd = er32(EECD);
	s32 ret_val = E1000_SUCCESS;
	u16 eeprom_size;

	switch (hw->mac_type) {
	case e1000_82542_rev2_0:
	case e1000_82542_rev2_1:
	case e1000_82543:
	case e1000_82544:
		eeprom->type = e1000_eeprom_microwire;
		eeprom->word_size = 64;
		eeprom->opcode_bits = 3;
		eeprom->address_bits = 6;
		eeprom->delay_usec = 50;
		break;
	case e1000_82540:
	case e1000_82545:
	case e1000_82545_rev_3:
	case e1000_82546:
	case e1000_82546_rev_3:
		eeprom->type = e1000_eeprom_microwire;
		eeprom->opcode_bits = 3;
		eeprom->delay_usec = 50;
		if (eecd & E1000_EECD_SIZE) {
			eeprom->word_size = 256;
			eeprom->address_bits = 8;
		} else {
			eeprom->word_size = 64;
			eeprom->address_bits = 6;
		}
		break;
	case e1000_82541:
	case e1000_82541_rev_2:
	case e1000_82547:
	case e1000_82547_rev_2:
		if (eecd & E1000_EECD_TYPE) {
			eeprom->type = e1000_eeprom_spi;
			eeprom->opcode_bits = 8;
			eeprom->delay_usec = 1;
			if (eecd & E1000_EECD_ADDR_BITS) {
				eeprom->page_size = 32;
				eeprom->address_bits = 16;
			} else {
				eeprom->page_size = 8;
				eeprom->address_bits = 8;
			}
		} else {
			eeprom->type = e1000_eeprom_microwire;
			eeprom->opcode_bits = 3;
			eeprom->delay_usec = 50;
			if (eecd & E1000_EECD_ADDR_BITS) {
				eeprom->word_size = 256;
				eeprom->address_bits = 8;
			} else {
				eeprom->word_size = 64;
				eeprom->address_bits = 6;
			}
		}
		break;
	default:
		break;
	}

	if (eeprom->type == e1000_eeprom_spi) {
		/* eeprom_size will be an enum [0..8] that maps to eeprom sizes
		 * 128B to 32KB (incremented by powers of 2).
		 */
		/* Set to default value for initial eeprom read. */
		eeprom->word_size = 64;
		ret_val = e1000_read_eeprom(hw, EEPROM_CFG, 1, &eeprom_size);
		if (ret_val)
			return ret_val;
		eeprom_size =
		    (eeprom_size & EEPROM_SIZE_MASK) >> EEPROM_SIZE_SHIFT;
		/* 256B eeprom size was not supported in earlier hardware, so we
		 * bump eeprom_size up one to ensure that "1" (which maps to
		 * 256B) is never the result used in the shifting logic below.
		 */
		if (eeprom_size)
			eeprom_size++;

		eeprom->word_size = 1 << (eeprom_size + EEPROM_WORD_SIZE_SHIFT);
	}
	return ret_val;
}