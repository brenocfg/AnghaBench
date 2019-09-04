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
struct e1000_hw {TYPE_1__* adapter; } ;
typedef  int s32 ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int E1000_ERR_CONFIG ; 
 int E1000_ERR_PHY ; 
 int E1000_EXTCNF_CTRL_SWFLAG ; 
 int /*<<< orphan*/  EXTCNF_CTRL ; 
 int /*<<< orphan*/  FWSM ; 
 int PHY_CFG_TIMEOUT ; 
 int SW_FLAG_TIMEOUT ; 
 int /*<<< orphan*/  __E1000_ACCESS_SHARED_RESOURCE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e_dbg (char*,...) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32 e1000_acquire_swflag_ich8lan(struct e1000_hw *hw)
{
	u32 extcnf_ctrl, timeout = PHY_CFG_TIMEOUT;
	s32 ret_val = 0;

	if (test_and_set_bit(__E1000_ACCESS_SHARED_RESOURCE,
			     &hw->adapter->state)) {
		e_dbg("contention for Phy access\n");
		return -E1000_ERR_PHY;
	}

	while (timeout) {
		extcnf_ctrl = er32(EXTCNF_CTRL);
		if (!(extcnf_ctrl & E1000_EXTCNF_CTRL_SWFLAG))
			break;

		mdelay(1);
		timeout--;
	}

	if (!timeout) {
		e_dbg("SW has already locked the resource.\n");
		ret_val = -E1000_ERR_CONFIG;
		goto out;
	}

	timeout = SW_FLAG_TIMEOUT;

	extcnf_ctrl |= E1000_EXTCNF_CTRL_SWFLAG;
	ew32(EXTCNF_CTRL, extcnf_ctrl);

	while (timeout) {
		extcnf_ctrl = er32(EXTCNF_CTRL);
		if (extcnf_ctrl & E1000_EXTCNF_CTRL_SWFLAG)
			break;

		mdelay(1);
		timeout--;
	}

	if (!timeout) {
		e_dbg("Failed to acquire the semaphore, FW or HW has it: FWSM=0x%8.8x EXTCNF_CTRL=0x%8.8x)\n",
		      er32(FWSM), extcnf_ctrl);
		extcnf_ctrl &= ~E1000_EXTCNF_CTRL_SWFLAG;
		ew32(EXTCNF_CTRL, extcnf_ctrl);
		ret_val = -E1000_ERR_CONFIG;
		goto out;
	}

out:
	if (ret_val)
		clear_bit(__E1000_ACCESS_SHARED_RESOURCE, &hw->adapter->state);

	return ret_val;
}