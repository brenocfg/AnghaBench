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
struct bnx2x_vlan_mac_obj {int /*<<< orphan*/  head_reader; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __bnx2x_vlan_mac_h_read_lock(struct bnx2x *bp,
					struct bnx2x_vlan_mac_obj *o)
{
	/* If we got here, we're holding lock --> no WRITER exists */
	o->head_reader++;
	DP(BNX2X_MSG_SP, "vlan_mac_lock - locked reader - number %d\n",
	   o->head_reader);

	return 0;
}