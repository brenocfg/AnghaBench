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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ID_LED_DEFAULT ; 
 int /*<<< orphan*/  ID_LED_DEFAULT_82573 ; 
 int /*<<< orphan*/  ID_LED_RESERVED_0000 ; 
 int /*<<< orphan*/  ID_LED_RESERVED_F746 ; 
 int /*<<< orphan*/  ID_LED_RESERVED_FFFF ; 
 int /*<<< orphan*/  NVM_ID_LED_SETTINGS ; 
#define  e1000_82573 130 
#define  e1000_82574 129 
#define  e1000_82583 128 
 scalar_t__ e1000_read_nvm (struct e1000_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 

__attribute__((used)) static s32 e1000_valid_led_default_82571(struct e1000_hw *hw, u16 *data)
{
	s32 ret_val;

	ret_val = e1000_read_nvm(hw, NVM_ID_LED_SETTINGS, 1, data);
	if (ret_val) {
		e_dbg("NVM Read Error\n");
		return ret_val;
	}

	switch (hw->mac.type) {
	case e1000_82573:
	case e1000_82574:
	case e1000_82583:
		if (*data == ID_LED_RESERVED_F746)
			*data = ID_LED_DEFAULT_82573;
		break;
	default:
		if (*data == ID_LED_RESERVED_0000 ||
		    *data == ID_LED_RESERVED_FFFF)
			*data = ID_LED_DEFAULT;
		break;
	}

	return 0;
}