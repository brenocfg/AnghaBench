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
typedef  void* u16 ;
struct ice_hw {int dummy; } ;
struct ice_fltr_mgmt_list_entry {int vsi_count; scalar_t__ sw_marker_id; TYPE_2__* vsi_list_info; int /*<<< orphan*/  lg_act_idx; } ;
struct TYPE_3__ {scalar_t__ hw_vsi_id; void* vsi_list_id; } ;
struct ice_fltr_info {scalar_t__ fltr_act; int /*<<< orphan*/  lkup_type; TYPE_1__ fwd_id; void* vsi_handle; int /*<<< orphan*/  fltr_rule_id; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
typedef  enum ice_adminq_opc { ____Placeholder_ice_adminq_opc } ice_adminq_opc ;
struct TYPE_4__ {int /*<<< orphan*/  vsi_map; } ;

/* Variables and functions */
 int ICE_ERR_ALREADY_EXISTS ; 
 int ICE_ERR_CFG ; 
 int ICE_ERR_NOT_IMPL ; 
 scalar_t__ ICE_FWD_TO_Q ; 
 scalar_t__ ICE_FWD_TO_QGRP ; 
 scalar_t__ ICE_FWD_TO_VSI ; 
 scalar_t__ ICE_FWD_TO_VSI_LIST ; 
 scalar_t__ ICE_INVAL_SW_MARKER_ID ; 
 int ice_add_marker_act (struct ice_hw*,struct ice_fltr_mgmt_list_entry*,scalar_t__,int /*<<< orphan*/ ) ; 
 int ice_aqc_opc_update_sw_rules ; 
 TYPE_2__* ice_create_vsi_list_map (struct ice_hw*,void**,int,void*) ; 
 int ice_create_vsi_list_rule (struct ice_hw*,void**,int,void**,int /*<<< orphan*/ ) ; 
 int ice_update_pkt_fwd_rule (struct ice_hw*,struct ice_fltr_info*) ; 
 int ice_update_vsi_list_rule (struct ice_hw*,void**,int,void*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ice_status
ice_add_update_vsi_list(struct ice_hw *hw,
			struct ice_fltr_mgmt_list_entry *m_entry,
			struct ice_fltr_info *cur_fltr,
			struct ice_fltr_info *new_fltr)
{
	enum ice_status status = 0;
	u16 vsi_list_id = 0;

	if ((cur_fltr->fltr_act == ICE_FWD_TO_Q ||
	     cur_fltr->fltr_act == ICE_FWD_TO_QGRP))
		return ICE_ERR_NOT_IMPL;

	if ((new_fltr->fltr_act == ICE_FWD_TO_Q ||
	     new_fltr->fltr_act == ICE_FWD_TO_QGRP) &&
	    (cur_fltr->fltr_act == ICE_FWD_TO_VSI ||
	     cur_fltr->fltr_act == ICE_FWD_TO_VSI_LIST))
		return ICE_ERR_NOT_IMPL;

	if (m_entry->vsi_count < 2 && !m_entry->vsi_list_info) {
		/* Only one entry existed in the mapping and it was not already
		 * a part of a VSI list. So, create a VSI list with the old and
		 * new VSIs.
		 */
		struct ice_fltr_info tmp_fltr;
		u16 vsi_handle_arr[2];

		/* A rule already exists with the new VSI being added */
		if (cur_fltr->fwd_id.hw_vsi_id == new_fltr->fwd_id.hw_vsi_id)
			return ICE_ERR_ALREADY_EXISTS;

		vsi_handle_arr[0] = cur_fltr->vsi_handle;
		vsi_handle_arr[1] = new_fltr->vsi_handle;
		status = ice_create_vsi_list_rule(hw, &vsi_handle_arr[0], 2,
						  &vsi_list_id,
						  new_fltr->lkup_type);
		if (status)
			return status;

		tmp_fltr = *new_fltr;
		tmp_fltr.fltr_rule_id = cur_fltr->fltr_rule_id;
		tmp_fltr.fltr_act = ICE_FWD_TO_VSI_LIST;
		tmp_fltr.fwd_id.vsi_list_id = vsi_list_id;
		/* Update the previous switch rule of "MAC forward to VSI" to
		 * "MAC fwd to VSI list"
		 */
		status = ice_update_pkt_fwd_rule(hw, &tmp_fltr);
		if (status)
			return status;

		cur_fltr->fwd_id.vsi_list_id = vsi_list_id;
		cur_fltr->fltr_act = ICE_FWD_TO_VSI_LIST;
		m_entry->vsi_list_info =
			ice_create_vsi_list_map(hw, &vsi_handle_arr[0], 2,
						vsi_list_id);

		/* If this entry was large action then the large action needs
		 * to be updated to point to FWD to VSI list
		 */
		if (m_entry->sw_marker_id != ICE_INVAL_SW_MARKER_ID)
			status =
			    ice_add_marker_act(hw, m_entry,
					       m_entry->sw_marker_id,
					       m_entry->lg_act_idx);
	} else {
		u16 vsi_handle = new_fltr->vsi_handle;
		enum ice_adminq_opc opcode;

		if (!m_entry->vsi_list_info)
			return ICE_ERR_CFG;

		/* A rule already exists with the new VSI being added */
		if (test_bit(vsi_handle, m_entry->vsi_list_info->vsi_map))
			return 0;

		/* Update the previously created VSI list set with
		 * the new VSI ID passed in
		 */
		vsi_list_id = cur_fltr->fwd_id.vsi_list_id;
		opcode = ice_aqc_opc_update_sw_rules;

		status = ice_update_vsi_list_rule(hw, &vsi_handle, 1,
						  vsi_list_id, false, opcode,
						  new_fltr->lkup_type);
		/* update VSI list mapping info with new VSI ID */
		if (!status)
			set_bit(vsi_handle, m_entry->vsi_list_info->vsi_map);
	}
	if (!status)
		m_entry->vsi_count++;
	return status;
}