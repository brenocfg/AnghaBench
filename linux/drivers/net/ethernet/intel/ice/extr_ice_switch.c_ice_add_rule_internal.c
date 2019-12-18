#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct mutex {int dummy; } ;
struct ice_switch_info {TYPE_1__* recp_list; } ;
struct ice_hw {TYPE_2__* port_info; struct ice_switch_info* switch_info; } ;
struct TYPE_6__ {int /*<<< orphan*/  hw_vsi_id; } ;
struct ice_fltr_info {int flag; TYPE_3__ fwd_id; int /*<<< orphan*/  src; int /*<<< orphan*/  vsi_handle; } ;
struct ice_fltr_mgmt_list_entry {struct ice_fltr_info fltr_info; } ;
struct ice_fltr_list_entry {struct ice_fltr_info fltr_info; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_5__ {int /*<<< orphan*/  lport; } ;
struct TYPE_4__ {struct mutex filt_rule_lock; } ;

/* Variables and functions */
 int ICE_ERR_PARAM ; 
 int ICE_FLTR_RX ; 
 int ICE_FLTR_TX ; 
 int ice_add_update_vsi_list (struct ice_hw*,struct ice_fltr_mgmt_list_entry*,struct ice_fltr_info*,struct ice_fltr_info*) ; 
 int ice_create_pkt_fwd_rule (struct ice_hw*,struct ice_fltr_list_entry*) ; 
 struct ice_fltr_mgmt_list_entry* ice_find_rule_entry (struct ice_hw*,size_t,struct ice_fltr_info*) ; 
 int /*<<< orphan*/  ice_get_hw_vsi_num (struct ice_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_is_vsi_valid (struct ice_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 

__attribute__((used)) static enum ice_status
ice_add_rule_internal(struct ice_hw *hw, u8 recp_id,
		      struct ice_fltr_list_entry *f_entry)
{
	struct ice_switch_info *sw = hw->switch_info;
	struct ice_fltr_info *new_fltr, *cur_fltr;
	struct ice_fltr_mgmt_list_entry *m_entry;
	struct mutex *rule_lock; /* Lock to protect filter rule list */
	enum ice_status status = 0;

	if (!ice_is_vsi_valid(hw, f_entry->fltr_info.vsi_handle))
		return ICE_ERR_PARAM;
	f_entry->fltr_info.fwd_id.hw_vsi_id =
		ice_get_hw_vsi_num(hw, f_entry->fltr_info.vsi_handle);

	rule_lock = &sw->recp_list[recp_id].filt_rule_lock;

	mutex_lock(rule_lock);
	new_fltr = &f_entry->fltr_info;
	if (new_fltr->flag & ICE_FLTR_RX)
		new_fltr->src = hw->port_info->lport;
	else if (new_fltr->flag & ICE_FLTR_TX)
		new_fltr->src = f_entry->fltr_info.fwd_id.hw_vsi_id;

	m_entry = ice_find_rule_entry(hw, recp_id, new_fltr);
	if (!m_entry) {
		mutex_unlock(rule_lock);
		return ice_create_pkt_fwd_rule(hw, f_entry);
	}

	cur_fltr = &m_entry->fltr_info;
	status = ice_add_update_vsi_list(hw, m_entry, cur_fltr, new_fltr);
	mutex_unlock(rule_lock);

	return status;
}