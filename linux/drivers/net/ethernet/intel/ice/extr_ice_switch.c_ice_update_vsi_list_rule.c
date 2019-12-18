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
typedef  int u16 ;
struct ice_hw {int dummy; } ;
struct TYPE_3__ {void* index; void* number_vsi; void** vsi; } ;
struct TYPE_4__ {TYPE_1__ vsi_list; } ;
struct ice_aqc_sw_rules_elem {TYPE_2__ pdata; void* type; } ;
typedef  enum ice_sw_lkup_type { ____Placeholder_ice_sw_lkup_type } ice_sw_lkup_type ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
typedef  enum ice_adminq_opc { ____Placeholder_ice_adminq_opc } ice_adminq_opc ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ICE_AQC_SW_RULES_T_PRUNE_LIST_CLEAR ; 
 int ICE_AQC_SW_RULES_T_PRUNE_LIST_SET ; 
 int ICE_AQC_SW_RULES_T_VSI_LIST_CLEAR ; 
 int ICE_AQC_SW_RULES_T_VSI_LIST_SET ; 
 int ICE_ERR_NO_MEMORY ; 
 int ICE_ERR_PARAM ; 
 int ICE_SW_LKUP_ETHERTYPE ; 
 int ICE_SW_LKUP_ETHERTYPE_MAC ; 
 int ICE_SW_LKUP_MAC ; 
 int ICE_SW_LKUP_MAC_VLAN ; 
 int ICE_SW_LKUP_PROMISC ; 
 int ICE_SW_LKUP_PROMISC_VLAN ; 
 int ICE_SW_LKUP_VLAN ; 
 scalar_t__ ICE_SW_RULE_VSI_LIST_SIZE (int) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct ice_aqc_sw_rules_elem*) ; 
 struct ice_aqc_sw_rules_elem* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ice_aq_sw_rules (struct ice_hw*,struct ice_aqc_sw_rules_elem*,int,int,int,int /*<<< orphan*/ *) ; 
 int ice_get_hw_vsi_num (struct ice_hw*,int) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_is_vsi_valid (struct ice_hw*,int) ; 

__attribute__((used)) static enum ice_status
ice_update_vsi_list_rule(struct ice_hw *hw, u16 *vsi_handle_arr, u16 num_vsi,
			 u16 vsi_list_id, bool remove, enum ice_adminq_opc opc,
			 enum ice_sw_lkup_type lkup_type)
{
	struct ice_aqc_sw_rules_elem *s_rule;
	enum ice_status status;
	u16 s_rule_size;
	u16 type;
	int i;

	if (!num_vsi)
		return ICE_ERR_PARAM;

	if (lkup_type == ICE_SW_LKUP_MAC ||
	    lkup_type == ICE_SW_LKUP_MAC_VLAN ||
	    lkup_type == ICE_SW_LKUP_ETHERTYPE ||
	    lkup_type == ICE_SW_LKUP_ETHERTYPE_MAC ||
	    lkup_type == ICE_SW_LKUP_PROMISC ||
	    lkup_type == ICE_SW_LKUP_PROMISC_VLAN)
		type = remove ? ICE_AQC_SW_RULES_T_VSI_LIST_CLEAR :
				ICE_AQC_SW_RULES_T_VSI_LIST_SET;
	else if (lkup_type == ICE_SW_LKUP_VLAN)
		type = remove ? ICE_AQC_SW_RULES_T_PRUNE_LIST_CLEAR :
				ICE_AQC_SW_RULES_T_PRUNE_LIST_SET;
	else
		return ICE_ERR_PARAM;

	s_rule_size = (u16)ICE_SW_RULE_VSI_LIST_SIZE(num_vsi);
	s_rule = devm_kzalloc(ice_hw_to_dev(hw), s_rule_size, GFP_KERNEL);
	if (!s_rule)
		return ICE_ERR_NO_MEMORY;
	for (i = 0; i < num_vsi; i++) {
		if (!ice_is_vsi_valid(hw, vsi_handle_arr[i])) {
			status = ICE_ERR_PARAM;
			goto exit;
		}
		/* AQ call requires hw_vsi_id(s) */
		s_rule->pdata.vsi_list.vsi[i] =
			cpu_to_le16(ice_get_hw_vsi_num(hw, vsi_handle_arr[i]));
	}

	s_rule->type = cpu_to_le16(type);
	s_rule->pdata.vsi_list.number_vsi = cpu_to_le16(num_vsi);
	s_rule->pdata.vsi_list.index = cpu_to_le16(vsi_list_id);

	status = ice_aq_sw_rules(hw, s_rule, s_rule_size, 1, opc, NULL);

exit:
	devm_kfree(ice_hw_to_dev(hw), s_rule);
	return status;
}