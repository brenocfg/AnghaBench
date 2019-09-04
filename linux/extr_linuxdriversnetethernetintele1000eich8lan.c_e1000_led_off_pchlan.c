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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  ledctl_mode1; } ;
struct e1000_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int E1000_LEDCTL_MODE_LINK_UP ; 
 int E1000_PHY_LED0_IVRT ; 
 int E1000_PHY_LED0_MASK ; 
 int E1000_PHY_LED0_MODE_MASK ; 
 int E1000_STATUS_LU ; 
 int /*<<< orphan*/  HV_LED_CONFIG ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  e1e_wphy (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int er32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 e1000_led_off_pchlan(struct e1000_hw *hw)
{
	u16 data = (u16)hw->mac.ledctl_mode1;
	u32 i, led;

	/* If no link, then turn LED off by clearing the invert bit
	 * for each LED that's mode is "link_up" in ledctl_mode1.
	 */
	if (!(er32(STATUS) & E1000_STATUS_LU)) {
		for (i = 0; i < 3; i++) {
			led = (data >> (i * 5)) & E1000_PHY_LED0_MASK;
			if ((led & E1000_PHY_LED0_MODE_MASK) !=
			    E1000_LEDCTL_MODE_LINK_UP)
				continue;
			if (led & E1000_PHY_LED0_IVRT)
				data &= ~(E1000_PHY_LED0_IVRT << (i * 5));
			else
				data |= (E1000_PHY_LED0_IVRT << (i * 5));
		}
	}

	return e1e_wphy(hw, HV_LED_CONFIG, data);
}