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
struct e1000_hw {scalar_t__ mac_type; int ledctl_default; int ledctl_mode1; int ledctl_mode2; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ERR_EEPROM ; 
 int E1000_LEDCTL_MODE_LED_OFF ; 
 int E1000_LEDCTL_MODE_LED_ON ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  EEPROM_ID_LED_SETTINGS ; 
#define  ID_LED_DEF1_OFF2 135 
#define  ID_LED_DEF1_ON2 134 
 int ID_LED_DEFAULT ; 
#define  ID_LED_OFF1_DEF2 133 
#define  ID_LED_OFF1_OFF2 132 
#define  ID_LED_OFF1_ON2 131 
#define  ID_LED_ON1_DEF2 130 
#define  ID_LED_ON1_OFF2 129 
#define  ID_LED_ON1_ON2 128 
 int ID_LED_RESERVED_0000 ; 
 int ID_LED_RESERVED_FFFF ; 
 int /*<<< orphan*/  LEDCTL ; 
 scalar_t__ e1000_82540 ; 
 scalar_t__ e1000_read_eeprom (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 e1000_id_led_init(struct e1000_hw *hw)
{
	u32 ledctl;
	const u32 ledctl_mask = 0x000000FF;
	const u32 ledctl_on = E1000_LEDCTL_MODE_LED_ON;
	const u32 ledctl_off = E1000_LEDCTL_MODE_LED_OFF;
	u16 eeprom_data, i, temp;
	const u16 led_mask = 0x0F;

	if (hw->mac_type < e1000_82540) {
		/* Nothing to do */
		return E1000_SUCCESS;
	}

	ledctl = er32(LEDCTL);
	hw->ledctl_default = ledctl;
	hw->ledctl_mode1 = hw->ledctl_default;
	hw->ledctl_mode2 = hw->ledctl_default;

	if (e1000_read_eeprom(hw, EEPROM_ID_LED_SETTINGS, 1, &eeprom_data) < 0) {
		e_dbg("EEPROM Read Error\n");
		return -E1000_ERR_EEPROM;
	}

	if ((eeprom_data == ID_LED_RESERVED_0000) ||
	    (eeprom_data == ID_LED_RESERVED_FFFF)) {
		eeprom_data = ID_LED_DEFAULT;
	}

	for (i = 0; i < 4; i++) {
		temp = (eeprom_data >> (i << 2)) & led_mask;
		switch (temp) {
		case ID_LED_ON1_DEF2:
		case ID_LED_ON1_ON2:
		case ID_LED_ON1_OFF2:
			hw->ledctl_mode1 &= ~(ledctl_mask << (i << 3));
			hw->ledctl_mode1 |= ledctl_on << (i << 3);
			break;
		case ID_LED_OFF1_DEF2:
		case ID_LED_OFF1_ON2:
		case ID_LED_OFF1_OFF2:
			hw->ledctl_mode1 &= ~(ledctl_mask << (i << 3));
			hw->ledctl_mode1 |= ledctl_off << (i << 3);
			break;
		default:
			/* Do nothing */
			break;
		}
		switch (temp) {
		case ID_LED_DEF1_ON2:
		case ID_LED_ON1_ON2:
		case ID_LED_OFF1_ON2:
			hw->ledctl_mode2 &= ~(ledctl_mask << (i << 3));
			hw->ledctl_mode2 |= ledctl_on << (i << 3);
			break;
		case ID_LED_DEF1_OFF2:
		case ID_LED_ON1_OFF2:
		case ID_LED_OFF1_OFF2:
			hw->ledctl_mode2 &= ~(ledctl_mask << (i << 3));
			hw->ledctl_mode2 |= ledctl_off << (i << 3);
			break;
		default:
			/* Do nothing */
			break;
		}
	}
	return E1000_SUCCESS;
}