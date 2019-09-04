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
struct bnx2x_vlan_mac_obj {scalar_t__ head_reader; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int EBUSY ; 

__attribute__((used)) static int __bnx2x_vlan_mac_h_write_trylock(struct bnx2x *bp,
					    struct bnx2x_vlan_mac_obj *o)
{
	if (o->head_reader) {
		DP(BNX2X_MSG_SP, "vlan_mac_lock writer - There are readers; Busy\n");
		return -EBUSY;
	}

	DP(BNX2X_MSG_SP, "vlan_mac_lock writer - Taken\n");
	return 0;
}