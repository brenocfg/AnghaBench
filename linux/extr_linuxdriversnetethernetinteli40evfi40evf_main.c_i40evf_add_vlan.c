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
struct i40evf_vlan_filter {int add; int /*<<< orphan*/  list; int /*<<< orphan*/  vlan; } ;
struct i40evf_adapter {int /*<<< orphan*/  mac_vlan_list_lock; int /*<<< orphan*/  aq_required; int /*<<< orphan*/  vlan_filter_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I40EVF_FLAG_AQ_ADD_VLAN_FILTER ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct i40evf_vlan_filter* i40evf_find_vlan (struct i40evf_adapter*,int /*<<< orphan*/ ) ; 
 struct i40evf_vlan_filter* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct
i40evf_vlan_filter *i40evf_add_vlan(struct i40evf_adapter *adapter, u16 vlan)
{
	struct i40evf_vlan_filter *f = NULL;

	spin_lock_bh(&adapter->mac_vlan_list_lock);

	f = i40evf_find_vlan(adapter, vlan);
	if (!f) {
		f = kzalloc(sizeof(*f), GFP_KERNEL);
		if (!f)
			goto clearout;

		f->vlan = vlan;

		INIT_LIST_HEAD(&f->list);
		list_add(&f->list, &adapter->vlan_filter_list);
		f->add = true;
		adapter->aq_required |= I40EVF_FLAG_AQ_ADD_VLAN_FILTER;
	}

clearout:
	spin_unlock_bh(&adapter->mac_vlan_list_lock);
	return f;
}