#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {int func; } ;
struct e1000_hw {TYPE_1__ phy; TYPE_2__ bus; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_EECD ; 
 int E1000_EECD_PRES ; 
 int /*<<< orphan*/  E1000_EEMNGCTL ; 
 int E1000_FUNC_2 ; 
 int E1000_FUNC_3 ; 
 int E1000_NVM_CFG_DONE_PORT_0 ; 
 int E1000_NVM_CFG_DONE_PORT_1 ; 
 int E1000_NVM_CFG_DONE_PORT_2 ; 
 int E1000_NVM_CFG_DONE_PORT_3 ; 
 scalar_t__ PHY_CFG_TIMEOUT ; 
 scalar_t__ e1000_phy_igp_3 ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 int /*<<< orphan*/  igb_phy_init_script_igp3 (struct e1000_hw*) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static s32 igb_get_cfg_done_82575(struct e1000_hw *hw)
{
	s32 timeout = PHY_CFG_TIMEOUT;
	u32 mask = E1000_NVM_CFG_DONE_PORT_0;

	if (hw->bus.func == 1)
		mask = E1000_NVM_CFG_DONE_PORT_1;
	else if (hw->bus.func == E1000_FUNC_2)
		mask = E1000_NVM_CFG_DONE_PORT_2;
	else if (hw->bus.func == E1000_FUNC_3)
		mask = E1000_NVM_CFG_DONE_PORT_3;

	while (timeout) {
		if (rd32(E1000_EEMNGCTL) & mask)
			break;
		usleep_range(1000, 2000);
		timeout--;
	}
	if (!timeout)
		hw_dbg("MNG configuration cycle has not completed.\n");

	/* If EEPROM is not marked present, init the PHY manually */
	if (((rd32(E1000_EECD) & E1000_EECD_PRES) == 0) &&
	    (hw->phy.type == e1000_phy_igp_3))
		igb_phy_init_script_igp3(hw);

	return 0;
}