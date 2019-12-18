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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ice_sq_cd {int dummy; } ;
struct ice_hw {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_rules_fltr_entry_index; } ;
struct TYPE_4__ {TYPE_1__ sw_rules; } ;
struct ice_aq_desc {TYPE_2__ params; int /*<<< orphan*/  flags; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
typedef  enum ice_adminq_opc { ____Placeholder_ice_adminq_opc } ice_adminq_opc ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_AQ_FLAG_RD ; 
 int ICE_ERR_PARAM ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int ice_aq_send_cmd (struct ice_hw*,struct ice_aq_desc*,void*,int /*<<< orphan*/ ,struct ice_sq_cd*) ; 
 int ice_aqc_opc_add_sw_rules ; 
 int ice_aqc_opc_remove_sw_rules ; 
 int ice_aqc_opc_update_sw_rules ; 
 int /*<<< orphan*/  ice_fill_dflt_direct_cmd_desc (struct ice_aq_desc*,int) ; 

__attribute__((used)) static enum ice_status
ice_aq_sw_rules(struct ice_hw *hw, void *rule_list, u16 rule_list_sz,
		u8 num_rules, enum ice_adminq_opc opc, struct ice_sq_cd *cd)
{
	struct ice_aq_desc desc;

	if (opc != ice_aqc_opc_add_sw_rules &&
	    opc != ice_aqc_opc_update_sw_rules &&
	    opc != ice_aqc_opc_remove_sw_rules)
		return ICE_ERR_PARAM;

	ice_fill_dflt_direct_cmd_desc(&desc, opc);

	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);
	desc.params.sw_rules.num_rules_fltr_entry_index =
		cpu_to_le16(num_rules);
	return ice_aq_send_cmd(hw, &desc, rule_list, rule_list_sz, cd);
}