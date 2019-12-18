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
struct bnx2x_vlan_mac_obj {unsigned long saved_ramrod_flags; int head_exe_request; int /*<<< orphan*/  exe_queue; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int bnx2x_exe_queue_step (struct bnx2x*,int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  bnx2x_panic () ; 

__attribute__((used)) static void __bnx2x_vlan_mac_h_exec_pending(struct bnx2x *bp,
					    struct bnx2x_vlan_mac_obj *o)
{
	int rc;
	unsigned long ramrod_flags = o->saved_ramrod_flags;

	DP(BNX2X_MSG_SP, "vlan_mac_lock execute pending command with ramrod flags %lu\n",
	   ramrod_flags);
	o->head_exe_request = false;
	o->saved_ramrod_flags = 0;
	rc = bnx2x_exe_queue_step(bp, &o->exe_queue, &ramrod_flags);
	if ((rc != 0) && (rc != 1)) {
		BNX2X_ERR("execution of pending commands failed with rc %d\n",
			  rc);
#ifdef BNX2X_STOP_ON_ERROR
		bnx2x_panic();
#endif
	}
}