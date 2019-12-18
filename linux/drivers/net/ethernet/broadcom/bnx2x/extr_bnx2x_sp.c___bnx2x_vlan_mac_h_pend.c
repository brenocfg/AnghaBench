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
struct bnx2x_vlan_mac_obj {int head_exe_request; unsigned long saved_ramrod_flags; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,unsigned long) ; 

__attribute__((used)) static void __bnx2x_vlan_mac_h_pend(struct bnx2x *bp,
				    struct bnx2x_vlan_mac_obj *o,
				    unsigned long ramrod_flags)
{
	o->head_exe_request = true;
	o->saved_ramrod_flags = ramrod_flags;
	DP(BNX2X_MSG_SP, "Placing pending execution with ramrod flags %lu\n",
	   ramrod_flags);
}