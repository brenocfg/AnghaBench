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
 int /*<<< orphan*/  IGC_EECD ; 
 scalar_t__ IGC_EECD_FLUDONE_I225 ; 
 scalar_t__ IGC_ERR_NVM ; 
 scalar_t__ IGC_FLUDONE_ATTEMPTS ; 
 scalar_t__ rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static s32 igc_pool_flash_update_done_i225(struct igc_hw *hw)
{
	s32 ret_val = -IGC_ERR_NVM;
	u32 i, reg;

	for (i = 0; i < IGC_FLUDONE_ATTEMPTS; i++) {
		reg = rd32(IGC_EECD);
		if (reg & IGC_EECD_FLUDONE_I225) {
			ret_val = 0;
			break;
		}
		udelay(5);
	}

	return ret_val;
}