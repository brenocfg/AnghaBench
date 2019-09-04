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
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int E1000_CTRL_GIO_MASTER_DISABLE ; 
 scalar_t__ E1000_ERR_MASTER_REQUESTS_PENDING ; 
 int E1000_STATUS_GIO_MASTER_ENABLE ; 
 scalar_t__ MASTER_DISABLE_TIMEOUT ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

s32 e1000e_disable_pcie_master(struct e1000_hw *hw)
{
	u32 ctrl;
	s32 timeout = MASTER_DISABLE_TIMEOUT;

	ctrl = er32(CTRL);
	ctrl |= E1000_CTRL_GIO_MASTER_DISABLE;
	ew32(CTRL, ctrl);

	while (timeout) {
		if (!(er32(STATUS) & E1000_STATUS_GIO_MASTER_ENABLE))
			break;
		usleep_range(100, 200);
		timeout--;
	}

	if (!timeout) {
		e_dbg("Master requests are pending.\n");
		return -E1000_ERR_MASTER_REQUESTS_PENDING;
	}

	return 0;
}