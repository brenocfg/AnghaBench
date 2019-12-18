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
 int /*<<< orphan*/  IGC_CTRL ; 
 int IGC_CTRL_GIO_MASTER_DISABLE ; 
 scalar_t__ IGC_ERR_MASTER_REQUESTS_PENDING ; 
 int /*<<< orphan*/  IGC_STATUS ; 
 int IGC_STATUS_GIO_MASTER_ENABLE ; 
 scalar_t__ MASTER_DISABLE_TIMEOUT ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

s32 igc_disable_pcie_master(struct igc_hw *hw)
{
	s32 timeout = MASTER_DISABLE_TIMEOUT;
	s32 ret_val = 0;
	u32 ctrl;

	ctrl = rd32(IGC_CTRL);
	ctrl |= IGC_CTRL_GIO_MASTER_DISABLE;
	wr32(IGC_CTRL, ctrl);

	while (timeout) {
		if (!(rd32(IGC_STATUS) &
		    IGC_STATUS_GIO_MASTER_ENABLE))
			break;
		usleep_range(2000, 3000);
		timeout--;
	}

	if (!timeout) {
		hw_dbg("Master requests are pending.\n");
		ret_val = -IGC_ERR_MASTER_REQUESTS_PENDING;
		goto out;
	}

out:
	return ret_val;
}