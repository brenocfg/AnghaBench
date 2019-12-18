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
struct bnx2x_vlan_mac_obj {scalar_t__ head_exe_request; int /*<<< orphan*/  head_reader; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  __bnx2x_vlan_mac_h_write_unlock (struct bnx2x*,struct bnx2x_vlan_mac_obj*) ; 
 int /*<<< orphan*/  bnx2x_panic () ; 

__attribute__((used)) static void __bnx2x_vlan_mac_h_read_unlock(struct bnx2x *bp,
					  struct bnx2x_vlan_mac_obj *o)
{
	if (!o->head_reader) {
		BNX2X_ERR("Need to release vlan mac reader lock, but lock isn't taken\n");
#ifdef BNX2X_STOP_ON_ERROR
		bnx2x_panic();
#endif
	} else {
		o->head_reader--;
		DP(BNX2X_MSG_SP, "vlan_mac_lock - decreased readers to %d\n",
		   o->head_reader);
	}

	/* It's possible a new pending execution was added, and that this reader
	 * was last - if so we need to execute the command.
	 */
	if (!o->head_reader && o->head_exe_request) {
		DP(BNX2X_MSG_SP, "vlan_mac_lock - reader release encountered a pending request\n");

		/* Writer release will do the trick */
		__bnx2x_vlan_mac_h_write_unlock(bp, o);
	}
}