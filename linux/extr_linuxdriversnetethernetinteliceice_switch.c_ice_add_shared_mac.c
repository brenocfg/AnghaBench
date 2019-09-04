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
struct ice_hw {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * mac_addr; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct ice_fltr_info {TYPE_2__ l_data; } ;
struct ice_fltr_mgmt_list_entry {struct ice_fltr_info fltr_info; } ;
struct ice_fltr_list_entry {struct ice_fltr_info fltr_info; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int ice_create_pkt_fwd_rule (struct ice_hw*,struct ice_fltr_list_entry*) ; 
 struct ice_fltr_mgmt_list_entry* ice_find_mac_entry (struct ice_hw*,int /*<<< orphan*/ *) ; 
 int ice_handle_vsi_list_mgmt (struct ice_hw*,struct ice_fltr_mgmt_list_entry*,struct ice_fltr_info*,struct ice_fltr_info*) ; 

__attribute__((used)) static enum ice_status
ice_add_shared_mac(struct ice_hw *hw, struct ice_fltr_list_entry *f_entry)
{
	struct ice_fltr_info *new_fltr, *cur_fltr;
	struct ice_fltr_mgmt_list_entry *m_entry;

	new_fltr = &f_entry->fltr_info;

	m_entry = ice_find_mac_entry(hw, &new_fltr->l_data.mac.mac_addr[0]);
	if (!m_entry)
		return ice_create_pkt_fwd_rule(hw, f_entry);

	cur_fltr = &m_entry->fltr_info;

	return ice_handle_vsi_list_mgmt(hw, m_entry, cur_fltr, new_fltr);
}