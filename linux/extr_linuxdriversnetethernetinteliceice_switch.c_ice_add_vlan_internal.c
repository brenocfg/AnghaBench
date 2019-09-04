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
typedef  scalar_t__ u16 ;
struct ice_hw {int dummy; } ;
struct TYPE_6__ {scalar_t__ vsi_id; scalar_t__ vsi_list_id; } ;
struct TYPE_4__ {scalar_t__ vlan_id; } ;
struct TYPE_5__ {TYPE_1__ vlan; } ;
struct ice_fltr_info {scalar_t__ fltr_act; int lkup_type; TYPE_3__ fwd_id; TYPE_2__ l_data; } ;
struct ice_fltr_mgmt_list_entry {struct ice_fltr_info fltr_info; int /*<<< orphan*/  vsi_list_info; } ;
struct ice_fltr_list_entry {struct ice_fltr_info fltr_info; } ;
typedef  enum ice_sw_lkup_type { ____Placeholder_ice_sw_lkup_type } ice_sw_lkup_type ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int ICE_ERR_DOES_NOT_EXIST ; 
 int ICE_ERR_PARAM ; 
 scalar_t__ ICE_FWD_TO_VSI ; 
 scalar_t__ ICE_FWD_TO_VSI_LIST ; 
 scalar_t__ ICE_MAX_VLAN_ID ; 
 scalar_t__ ICE_VSI_INVAL_ID ; 
 int ice_create_pkt_fwd_rule (struct ice_hw*,struct ice_fltr_list_entry*) ; 
 int /*<<< orphan*/  ice_create_vsi_list_map (struct ice_hw*,scalar_t__*,int,scalar_t__) ; 
 int ice_create_vsi_list_rule (struct ice_hw*,scalar_t__*,int,scalar_t__*,int) ; 
 struct ice_fltr_mgmt_list_entry* ice_find_vlan_entry (struct ice_hw*,scalar_t__) ; 
 int ice_handle_vsi_list_mgmt (struct ice_hw*,struct ice_fltr_mgmt_list_entry*,struct ice_fltr_info*,struct ice_fltr_info*) ; 

__attribute__((used)) static enum ice_status
ice_add_vlan_internal(struct ice_hw *hw, struct ice_fltr_list_entry *f_entry)
{
	struct ice_fltr_info *new_fltr, *cur_fltr;
	struct ice_fltr_mgmt_list_entry *v_list_itr;
	u16 vlan_id;

	new_fltr = &f_entry->fltr_info;
	/* VLAN id should only be 12 bits */
	if (new_fltr->l_data.vlan.vlan_id > ICE_MAX_VLAN_ID)
		return ICE_ERR_PARAM;

	vlan_id = new_fltr->l_data.vlan.vlan_id;
	v_list_itr = ice_find_vlan_entry(hw, vlan_id);
	if (!v_list_itr) {
		u16 vsi_id = ICE_VSI_INVAL_ID;
		enum ice_status status;
		u16 vsi_list_id = 0;

		if (new_fltr->fltr_act == ICE_FWD_TO_VSI) {
			enum ice_sw_lkup_type lkup_type = new_fltr->lkup_type;

			/* All VLAN pruning rules use a VSI list.
			 * Convert the action to forwarding to a VSI list.
			 */
			vsi_id = new_fltr->fwd_id.vsi_id;
			status = ice_create_vsi_list_rule(hw, &vsi_id, 1,
							  &vsi_list_id,
							  lkup_type);
			if (status)
				return status;
			new_fltr->fltr_act = ICE_FWD_TO_VSI_LIST;
			new_fltr->fwd_id.vsi_list_id = vsi_list_id;
		}

		status = ice_create_pkt_fwd_rule(hw, f_entry);
		if (!status && vsi_id != ICE_VSI_INVAL_ID) {
			v_list_itr = ice_find_vlan_entry(hw, vlan_id);
			if (!v_list_itr)
				return ICE_ERR_DOES_NOT_EXIST;
			v_list_itr->vsi_list_info =
				ice_create_vsi_list_map(hw, &vsi_id, 1,
							vsi_list_id);
		}

		return status;
	}

	cur_fltr = &v_list_itr->fltr_info;
	return ice_handle_vsi_list_mgmt(hw, v_list_itr, cur_fltr, new_fltr);
}