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
typedef  int /*<<< orphan*/  u16 ;
struct ice_vsi_list_map_info {int /*<<< orphan*/  list_entry; int /*<<< orphan*/  vsi_map; } ;
struct ice_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_vsi_id; int /*<<< orphan*/  vsi_list_id; } ;
struct ice_fltr_info {scalar_t__ fltr_act; int lkup_type; TYPE_1__ fwd_id; int /*<<< orphan*/  vsi_handle; } ;
struct ice_fltr_mgmt_list_entry {scalar_t__ vsi_count; struct ice_vsi_list_map_info* vsi_list_info; struct ice_fltr_info fltr_info; } ;
typedef  enum ice_sw_lkup_type { ____Placeholder_ice_sw_lkup_type } ice_sw_lkup_type ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_DBG_SW ; 
 int ICE_ERR_DOES_NOT_EXIST ; 
 int ICE_ERR_OUT_OF_RANGE ; 
 int ICE_ERR_PARAM ; 
 scalar_t__ ICE_FWD_TO_VSI ; 
 scalar_t__ ICE_FWD_TO_VSI_LIST ; 
 int /*<<< orphan*/  ICE_MAX_VSI ; 
 int ICE_SW_LKUP_VLAN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct ice_vsi_list_map_info*) ; 
 int /*<<< orphan*/  find_first_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_aqc_opc_update_sw_rules ; 
 int /*<<< orphan*/  ice_debug (struct ice_hw*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ice_get_hw_vsi_num (struct ice_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_is_vsi_valid (struct ice_hw*,int /*<<< orphan*/ ) ; 
 int ice_remove_vsi_list_rule (struct ice_hw*,int /*<<< orphan*/ ,int) ; 
 int ice_update_pkt_fwd_rule (struct ice_hw*,struct ice_fltr_info*) ; 
 int ice_update_vsi_list_rule (struct ice_hw*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ice_status
ice_rem_update_vsi_list(struct ice_hw *hw, u16 vsi_handle,
			struct ice_fltr_mgmt_list_entry *fm_list)
{
	enum ice_sw_lkup_type lkup_type;
	enum ice_status status = 0;
	u16 vsi_list_id;

	if (fm_list->fltr_info.fltr_act != ICE_FWD_TO_VSI_LIST ||
	    fm_list->vsi_count == 0)
		return ICE_ERR_PARAM;

	/* A rule with the VSI being removed does not exist */
	if (!test_bit(vsi_handle, fm_list->vsi_list_info->vsi_map))
		return ICE_ERR_DOES_NOT_EXIST;

	lkup_type = fm_list->fltr_info.lkup_type;
	vsi_list_id = fm_list->fltr_info.fwd_id.vsi_list_id;
	status = ice_update_vsi_list_rule(hw, &vsi_handle, 1, vsi_list_id, true,
					  ice_aqc_opc_update_sw_rules,
					  lkup_type);
	if (status)
		return status;

	fm_list->vsi_count--;
	clear_bit(vsi_handle, fm_list->vsi_list_info->vsi_map);

	if (fm_list->vsi_count == 1 && lkup_type != ICE_SW_LKUP_VLAN) {
		struct ice_fltr_info tmp_fltr_info = fm_list->fltr_info;
		struct ice_vsi_list_map_info *vsi_list_info =
			fm_list->vsi_list_info;
		u16 rem_vsi_handle;

		rem_vsi_handle = find_first_bit(vsi_list_info->vsi_map,
						ICE_MAX_VSI);
		if (!ice_is_vsi_valid(hw, rem_vsi_handle))
			return ICE_ERR_OUT_OF_RANGE;

		/* Make sure VSI list is empty before removing it below */
		status = ice_update_vsi_list_rule(hw, &rem_vsi_handle, 1,
						  vsi_list_id, true,
						  ice_aqc_opc_update_sw_rules,
						  lkup_type);
		if (status)
			return status;

		tmp_fltr_info.fltr_act = ICE_FWD_TO_VSI;
		tmp_fltr_info.fwd_id.hw_vsi_id =
			ice_get_hw_vsi_num(hw, rem_vsi_handle);
		tmp_fltr_info.vsi_handle = rem_vsi_handle;
		status = ice_update_pkt_fwd_rule(hw, &tmp_fltr_info);
		if (status) {
			ice_debug(hw, ICE_DBG_SW,
				  "Failed to update pkt fwd rule to FWD_TO_VSI on HW VSI %d, error %d\n",
				  tmp_fltr_info.fwd_id.hw_vsi_id, status);
			return status;
		}

		fm_list->fltr_info = tmp_fltr_info;
	}

	if ((fm_list->vsi_count == 1 && lkup_type != ICE_SW_LKUP_VLAN) ||
	    (fm_list->vsi_count == 0 && lkup_type == ICE_SW_LKUP_VLAN)) {
		struct ice_vsi_list_map_info *vsi_list_info =
			fm_list->vsi_list_info;

		/* Remove the VSI list since it is no longer used */
		status = ice_remove_vsi_list_rule(hw, vsi_list_id, lkup_type);
		if (status) {
			ice_debug(hw, ICE_DBG_SW,
				  "Failed to remove VSI list %d, error %d\n",
				  vsi_list_id, status);
			return status;
		}

		list_del(&vsi_list_info->list_entry);
		devm_kfree(ice_hw_to_dev(hw), vsi_list_info);
		fm_list->vsi_list_info = NULL;
	}

	return status;
}