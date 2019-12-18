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
typedef  int /*<<< orphan*/  u16 ;
struct iavf_vlan_filter {int remove; } ;
struct iavf_adapter {int /*<<< orphan*/  mac_vlan_list_lock; int /*<<< orphan*/  aq_required; } ;

/* Variables and functions */
 int /*<<< orphan*/  IAVF_FLAG_AQ_DEL_VLAN_FILTER ; 
 struct iavf_vlan_filter* iavf_find_vlan (struct iavf_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iavf_del_vlan(struct iavf_adapter *adapter, u16 vlan)
{
	struct iavf_vlan_filter *f;

	spin_lock_bh(&adapter->mac_vlan_list_lock);

	f = iavf_find_vlan(adapter, vlan);
	if (f) {
		f->remove = true;
		adapter->aq_required |= IAVF_FLAG_AQ_DEL_VLAN_FILTER;
	}

	spin_unlock_bh(&adapter->mac_vlan_list_lock);
}