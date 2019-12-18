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
typedef  scalar_t__ u32 ;
struct igc_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_EERD ; 
 int /*<<< orphan*/  IGC_EEWR ; 
 scalar_t__ IGC_ERR_NVM ; 
 int IGC_NVM_POLL_READ ; 
 scalar_t__ IGC_NVM_RW_REG_DONE ; 
 scalar_t__ rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static s32 igc_poll_eerd_eewr_done(struct igc_hw *hw, int ee_reg)
{
	s32 ret_val = -IGC_ERR_NVM;
	u32 attempts = 100000;
	u32 i, reg = 0;

	for (i = 0; i < attempts; i++) {
		if (ee_reg == IGC_NVM_POLL_READ)
			reg = rd32(IGC_EERD);
		else
			reg = rd32(IGC_EEWR);

		if (reg & IGC_NVM_RW_REG_DONE) {
			ret_val = 0;
			break;
		}

		udelay(5);
	}

	return ret_val;
}