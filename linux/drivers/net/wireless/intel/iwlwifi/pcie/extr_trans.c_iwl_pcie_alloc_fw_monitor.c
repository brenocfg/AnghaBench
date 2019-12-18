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
typedef  int u8 ;
struct TYPE_2__ {scalar_t__ num_blocks; } ;
struct iwl_trans {TYPE_1__ dbg; } ;

/* Variables and functions */
 scalar_t__ WARN (int,char*,int) ; 
 int /*<<< orphan*/  iwl_pcie_alloc_fw_monitor_block (struct iwl_trans*,int,int) ; 

void iwl_pcie_alloc_fw_monitor(struct iwl_trans *trans, u8 max_power)
{
	if (!max_power) {
		/* default max_power is maximum */
		max_power = 26;
	} else {
		max_power += 11;
	}

	if (WARN(max_power > 26,
		 "External buffer size for monitor is too big %d, check the FW TLV\n",
		 max_power))
		return;

	/*
	 * This function allocats the default fw monitor.
	 * The optional additional ones will be allocated in runtime
	 */
	if (trans->dbg.num_blocks)
		return;

	iwl_pcie_alloc_fw_monitor_block(trans, max_power, 11);
}