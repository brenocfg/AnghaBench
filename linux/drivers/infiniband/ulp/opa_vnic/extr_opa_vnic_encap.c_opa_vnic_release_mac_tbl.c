#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ mac_tbl_digest; } ;
struct TYPE_4__ {TYPE_1__ vport; } ;
struct opa_vnic_adapter {int /*<<< orphan*/  mactbl_lock; TYPE_2__ info; int /*<<< orphan*/  mactbl; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opa_vnic_free_mac_tbl (struct hlist_head*) ; 
 struct hlist_head* rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void opa_vnic_release_mac_tbl(struct opa_vnic_adapter *adapter)
{
	struct hlist_head *mactbl;

	mutex_lock(&adapter->mactbl_lock);
	mactbl = rcu_access_pointer(adapter->mactbl);
	rcu_assign_pointer(adapter->mactbl, NULL);
	synchronize_rcu();
	opa_vnic_free_mac_tbl(mactbl);
	adapter->info.vport.mac_tbl_digest = 0;
	mutex_unlock(&adapter->mactbl_lock);
}