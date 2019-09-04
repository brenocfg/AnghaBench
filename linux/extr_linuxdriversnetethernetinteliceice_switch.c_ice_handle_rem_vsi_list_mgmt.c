#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_5__ {scalar_t__ vsi_list_id; scalar_t__ vsi_id; } ;
struct TYPE_8__ {int lkup_type; scalar_t__ fltr_act; int /*<<< orphan*/  fltr_rule_id; TYPE_1__ fwd_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  index; } ;
struct TYPE_7__ {TYPE_2__ lkup_tx_rx; } ;
struct ice_vsi_list_map_info {int vsi_count; int /*<<< orphan*/  list_entry; TYPE_4__ fltr_info; TYPE_3__ pdata; struct ice_vsi_list_map_info* vsi_list_info; int /*<<< orphan*/  vsi_map; } ;
struct ice_switch_info {int /*<<< orphan*/  mac_list_lock; } ;
struct ice_hw {struct ice_switch_info* switch_info; } ;
struct ice_fltr_mgmt_list_entry {int vsi_count; int /*<<< orphan*/  list_entry; TYPE_4__ fltr_info; TYPE_3__ pdata; struct ice_fltr_mgmt_list_entry* vsi_list_info; int /*<<< orphan*/  vsi_map; } ;
struct ice_aqc_sw_rules_elem {int vsi_count; int /*<<< orphan*/  list_entry; TYPE_4__ fltr_info; TYPE_3__ pdata; struct ice_aqc_sw_rules_elem* vsi_list_info; int /*<<< orphan*/  vsi_map; } ;
typedef  enum ice_sw_lkup_type { ____Placeholder_ice_sw_lkup_type } ice_sw_lkup_type ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ICE_ERR_NO_MEMORY ; 
 int ICE_ERR_OUT_OF_RANGE ; 
 scalar_t__ ICE_FWD_TO_VSI ; 
 scalar_t__ ICE_FWD_TO_VSI_LIST ; 
 scalar_t__ ICE_MAX_VSI ; 
 int ICE_SW_LKUP_VLAN ; 
 int /*<<< orphan*/  ICE_SW_RULE_RX_TX_ETH_HDR_SIZE ; 
 int /*<<< orphan*/  ICE_SW_RULE_RX_TX_NO_HDR_SIZE ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct ice_vsi_list_map_info*) ; 
 struct ice_vsi_list_map_info* devm_kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ find_first_bit (int /*<<< orphan*/ ,scalar_t__) ; 
 int ice_aq_sw_rules (struct ice_hw*,struct ice_vsi_list_map_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_aqc_opc_remove_sw_rules ; 
 int /*<<< orphan*/  ice_aqc_opc_update_sw_rules ; 
 int /*<<< orphan*/  ice_fill_sw_rule (struct ice_hw*,TYPE_4__*,struct ice_vsi_list_map_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 
 int ice_remove_vsi_list_rule (struct ice_hw*,scalar_t__,int) ; 
 int ice_update_vsi_list_rule (struct ice_hw*,scalar_t__*,int,scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum ice_status
ice_handle_rem_vsi_list_mgmt(struct ice_hw *hw, u16 vsi_id,
			     struct ice_fltr_mgmt_list_entry *fm_list_itr)
{
	struct ice_switch_info *sw = hw->switch_info;
	enum ice_status status = 0;
	enum ice_sw_lkup_type lkup_type;
	bool is_last_elem = true;
	bool conv_list = false;
	bool del_list = false;
	u16 vsi_list_id;

	lkup_type = fm_list_itr->fltr_info.lkup_type;
	vsi_list_id = fm_list_itr->fltr_info.fwd_id.vsi_list_id;

	if (fm_list_itr->vsi_count > 1) {
		status = ice_update_vsi_list_rule(hw, &vsi_id, 1, vsi_list_id,
						  true,
						  ice_aqc_opc_update_sw_rules,
						  lkup_type);
		if (status)
			return status;
		fm_list_itr->vsi_count--;
		is_last_elem = false;
		clear_bit(vsi_id, fm_list_itr->vsi_list_info->vsi_map);
	}

	/* For non-VLAN rules that forward packets to a VSI list, convert them
	 * to forwarding packets to a VSI if there is only one VSI left in the
	 * list.  Unused lists are then removed.
	 * VLAN rules need to use VSI lists even with only one VSI.
	 */
	if (fm_list_itr->fltr_info.fltr_act == ICE_FWD_TO_VSI_LIST) {
		if (lkup_type == ICE_SW_LKUP_VLAN) {
			del_list = is_last_elem;
		} else if (fm_list_itr->vsi_count == 1) {
			conv_list = true;
			del_list = true;
		}
	}

	if (del_list) {
		/* Remove the VSI list since it is no longer used */
		struct ice_vsi_list_map_info *vsi_list_info =
			fm_list_itr->vsi_list_info;

		status = ice_remove_vsi_list_rule(hw, vsi_list_id, lkup_type);
		if (status)
			return status;

		if (conv_list) {
			u16 rem_vsi_id;

			rem_vsi_id = find_first_bit(vsi_list_info->vsi_map,
						    ICE_MAX_VSI);

			/* Error out when the expected last element is not in
			 * the VSI list map
			 */
			if (rem_vsi_id == ICE_MAX_VSI)
				return ICE_ERR_OUT_OF_RANGE;

			/* Change the list entry action from VSI_LIST to VSI */
			fm_list_itr->fltr_info.fltr_act = ICE_FWD_TO_VSI;
			fm_list_itr->fltr_info.fwd_id.vsi_id = rem_vsi_id;
		}

		list_del(&vsi_list_info->list_entry);
		devm_kfree(ice_hw_to_dev(hw), vsi_list_info);
		fm_list_itr->vsi_list_info = NULL;
	}

	if (conv_list) {
		/* Convert the rule's forward action to forwarding packets to
		 * a VSI
		 */
		struct ice_aqc_sw_rules_elem *s_rule;

		s_rule = devm_kzalloc(ice_hw_to_dev(hw),
				      ICE_SW_RULE_RX_TX_ETH_HDR_SIZE,
				      GFP_KERNEL);
		if (!s_rule)
			return ICE_ERR_NO_MEMORY;

		ice_fill_sw_rule(hw, &fm_list_itr->fltr_info, s_rule,
				 ice_aqc_opc_update_sw_rules);

		s_rule->pdata.lkup_tx_rx.index =
			cpu_to_le16(fm_list_itr->fltr_info.fltr_rule_id);

		status = ice_aq_sw_rules(hw, s_rule,
					 ICE_SW_RULE_RX_TX_ETH_HDR_SIZE, 1,
					 ice_aqc_opc_update_sw_rules, NULL);
		devm_kfree(ice_hw_to_dev(hw), s_rule);
		if (status)
			return status;
	}

	if (is_last_elem) {
		/* Remove the lookup rule */
		struct ice_aqc_sw_rules_elem *s_rule;

		s_rule = devm_kzalloc(ice_hw_to_dev(hw),
				      ICE_SW_RULE_RX_TX_NO_HDR_SIZE,
				      GFP_KERNEL);
		if (!s_rule)
			return ICE_ERR_NO_MEMORY;

		ice_fill_sw_rule(hw, &fm_list_itr->fltr_info, s_rule,
				 ice_aqc_opc_remove_sw_rules);

		status = ice_aq_sw_rules(hw, s_rule,
					 ICE_SW_RULE_RX_TX_NO_HDR_SIZE, 1,
					 ice_aqc_opc_remove_sw_rules, NULL);
		if (status)
			return status;

		/* Remove a book keeping entry from the MAC address list */
		mutex_lock(&sw->mac_list_lock);
		list_del(&fm_list_itr->list_entry);
		mutex_unlock(&sw->mac_list_lock);
		devm_kfree(ice_hw_to_dev(hw), fm_list_itr);
		devm_kfree(ice_hw_to_dev(hw), s_rule);
	}
	return status;
}