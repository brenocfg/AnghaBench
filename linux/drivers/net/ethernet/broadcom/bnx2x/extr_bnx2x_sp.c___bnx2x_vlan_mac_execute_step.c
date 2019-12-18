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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct bnx2x_vlan_mac_obj {TYPE_1__ exe_queue; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  __bnx2x_vlan_mac_h_pend (struct bnx2x*,struct bnx2x_vlan_mac_obj*,unsigned long) ; 
 int __bnx2x_vlan_mac_h_write_trylock (struct bnx2x*,struct bnx2x_vlan_mac_obj*) ; 
 int bnx2x_exe_queue_step (struct bnx2x*,TYPE_1__*,unsigned long*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __bnx2x_vlan_mac_execute_step(struct bnx2x *bp,
					 struct bnx2x_vlan_mac_obj *o,
					 unsigned long *ramrod_flags)
{
	int rc = 0;

	spin_lock_bh(&o->exe_queue.lock);

	DP(BNX2X_MSG_SP, "vlan_mac_execute_step - trying to take writer lock\n");
	rc = __bnx2x_vlan_mac_h_write_trylock(bp, o);

	if (rc != 0) {
		__bnx2x_vlan_mac_h_pend(bp, o, *ramrod_flags);

		/* Calling function should not differentiate between this case
		 * and the case in which there is already a pending ramrod
		 */
		rc = 1;
	} else {
		rc = bnx2x_exe_queue_step(bp, &o->exe_queue, ramrod_flags);
	}
	spin_unlock_bh(&o->exe_queue.lock);

	return rc;
}