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
 int /*<<< orphan*/  __bnx2x_vlan_mac_h_read_unlock (struct bnx2x*,struct bnx2x_vlan_mac_obj*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void bnx2x_vlan_mac_h_read_unlock(struct bnx2x *bp,
				  struct bnx2x_vlan_mac_obj *o)
{
	spin_lock_bh(&o->exe_queue.lock);
	__bnx2x_vlan_mac_h_read_unlock(bp, o);
	spin_unlock_bh(&o->exe_queue.lock);
}