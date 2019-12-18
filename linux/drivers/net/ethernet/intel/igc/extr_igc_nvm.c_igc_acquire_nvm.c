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
struct igc_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_EECD ; 
 int IGC_EECD_GNT ; 
 int IGC_EECD_REQ ; 
 scalar_t__ IGC_ERR_NVM ; 
 scalar_t__ IGC_NVM_GRANT_ATTEMPTS ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

s32 igc_acquire_nvm(struct igc_hw *hw)
{
	s32 timeout = IGC_NVM_GRANT_ATTEMPTS;
	u32 eecd = rd32(IGC_EECD);
	s32 ret_val = 0;

	wr32(IGC_EECD, eecd | IGC_EECD_REQ);
	eecd = rd32(IGC_EECD);

	while (timeout) {
		if (eecd & IGC_EECD_GNT)
			break;
		udelay(5);
		eecd = rd32(IGC_EECD);
		timeout--;
	}

	if (!timeout) {
		eecd &= ~IGC_EECD_REQ;
		wr32(IGC_EECD, eecd);
		hw_dbg("Could not acquire NVM grant\n");
		ret_val = -IGC_ERR_NVM;
	}

	return ret_val;
}