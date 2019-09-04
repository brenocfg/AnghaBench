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
struct e1000_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ERR_NVM ; 
 int E1000_NVM_POLL_READ ; 
 scalar_t__ E1000_NVM_RW_REG_DONE ; 
 int /*<<< orphan*/  EERD ; 
 int /*<<< orphan*/  EEWR ; 
 scalar_t__ er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

s32 e1000e_poll_eerd_eewr_done(struct e1000_hw *hw, int ee_reg)
{
	u32 attempts = 100000;
	u32 i, reg = 0;

	for (i = 0; i < attempts; i++) {
		if (ee_reg == E1000_NVM_POLL_READ)
			reg = er32(EERD);
		else
			reg = er32(EEWR);

		if (reg & E1000_NVM_RW_REG_DONE)
			return 0;

		udelay(5);
	}

	return -E1000_ERR_NVM;
}