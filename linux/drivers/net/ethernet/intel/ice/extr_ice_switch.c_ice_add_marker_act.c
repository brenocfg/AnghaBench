#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct ice_hw {int dummy; } ;
struct TYPE_6__ {int vsi_list_id; int hw_vsi_id; } ;
struct TYPE_10__ {scalar_t__ lkup_type; int const fltr_rule_id; TYPE_1__ fwd_id; } ;
struct ice_fltr_mgmt_list_entry {int vsi_count; int lg_act_idx; int sw_marker_id; TYPE_5__ fltr_info; } ;
struct TYPE_8__ {void* index; void* act; } ;
struct TYPE_7__ {void** act; void* size; void* index; } ;
struct TYPE_9__ {TYPE_3__ lkup_tx_rx; TYPE_2__ lg_act; } ;
struct ice_aqc_sw_rules_elem {TYPE_4__ pdata; void* type; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int const ICE_AQC_SW_RULES_T_LG_ACT ; 
 int ICE_ERR_NO_MEMORY ; 
 int ICE_ERR_PARAM ; 
 int ICE_LG_ACT_GENERIC ; 
 int ICE_LG_ACT_GENERIC_OFFSET_M ; 
 int ICE_LG_ACT_GENERIC_OFFSET_S ; 
 int ICE_LG_ACT_GENERIC_OFF_RX_DESC_PROF_IDX ; 
 int ICE_LG_ACT_GENERIC_VALUE_M ; 
 int ICE_LG_ACT_GENERIC_VALUE_S ; 
 int ICE_LG_ACT_VALID_BIT ; 
 int ICE_LG_ACT_VSI_FORWARDING ; 
 int ICE_LG_ACT_VSI_LIST ; 
 int ICE_LG_ACT_VSI_LIST_ID_M ; 
 int ICE_LG_ACT_VSI_LIST_ID_S ; 
 int ICE_SINGLE_ACT_PTR ; 
 int ICE_SINGLE_ACT_PTR_VAL_M ; 
 int ICE_SINGLE_ACT_PTR_VAL_S ; 
 scalar_t__ ICE_SW_LKUP_MAC ; 
 scalar_t__ ICE_SW_RULE_LG_ACT_SIZE (int const) ; 
 int ICE_SW_RULE_RX_TX_ETH_HDR_SIZE ; 
 void* cpu_to_le16 (int const) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct ice_aqc_sw_rules_elem*) ; 
 struct ice_aqc_sw_rules_elem* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ice_aq_sw_rules (struct ice_hw*,struct ice_aqc_sw_rules_elem*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_aqc_opc_update_sw_rules ; 
 int /*<<< orphan*/  ice_fill_sw_rule (struct ice_hw*,TYPE_5__*,struct ice_aqc_sw_rules_elem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 

__attribute__((used)) static enum ice_status
ice_add_marker_act(struct ice_hw *hw, struct ice_fltr_mgmt_list_entry *m_ent,
		   u16 sw_marker, u16 l_id)
{
	struct ice_aqc_sw_rules_elem *lg_act, *rx_tx;
	/* For software marker we need 3 large actions
	 * 1. FWD action: FWD TO VSI or VSI LIST
	 * 2. GENERIC VALUE action to hold the profile ID
	 * 3. GENERIC VALUE action to hold the software marker ID
	 */
	const u16 num_lg_acts = 3;
	enum ice_status status;
	u16 lg_act_size;
	u16 rules_size;
	u32 act;
	u16 id;

	if (m_ent->fltr_info.lkup_type != ICE_SW_LKUP_MAC)
		return ICE_ERR_PARAM;

	/* Create two back-to-back switch rules and submit them to the HW using
	 * one memory buffer:
	 *    1. Large Action
	 *    2. Look up Tx Rx
	 */
	lg_act_size = (u16)ICE_SW_RULE_LG_ACT_SIZE(num_lg_acts);
	rules_size = lg_act_size + ICE_SW_RULE_RX_TX_ETH_HDR_SIZE;
	lg_act = devm_kzalloc(ice_hw_to_dev(hw), rules_size, GFP_KERNEL);
	if (!lg_act)
		return ICE_ERR_NO_MEMORY;

	rx_tx = (struct ice_aqc_sw_rules_elem *)((u8 *)lg_act + lg_act_size);

	/* Fill in the first switch rule i.e. large action */
	lg_act->type = cpu_to_le16(ICE_AQC_SW_RULES_T_LG_ACT);
	lg_act->pdata.lg_act.index = cpu_to_le16(l_id);
	lg_act->pdata.lg_act.size = cpu_to_le16(num_lg_acts);

	/* First action VSI forwarding or VSI list forwarding depending on how
	 * many VSIs
	 */
	id = (m_ent->vsi_count > 1) ? m_ent->fltr_info.fwd_id.vsi_list_id :
		m_ent->fltr_info.fwd_id.hw_vsi_id;

	act = ICE_LG_ACT_VSI_FORWARDING | ICE_LG_ACT_VALID_BIT;
	act |= (id << ICE_LG_ACT_VSI_LIST_ID_S) &
		ICE_LG_ACT_VSI_LIST_ID_M;
	if (m_ent->vsi_count > 1)
		act |= ICE_LG_ACT_VSI_LIST;
	lg_act->pdata.lg_act.act[0] = cpu_to_le32(act);

	/* Second action descriptor type */
	act = ICE_LG_ACT_GENERIC;

	act |= (1 << ICE_LG_ACT_GENERIC_VALUE_S) & ICE_LG_ACT_GENERIC_VALUE_M;
	lg_act->pdata.lg_act.act[1] = cpu_to_le32(act);

	act = (ICE_LG_ACT_GENERIC_OFF_RX_DESC_PROF_IDX <<
	       ICE_LG_ACT_GENERIC_OFFSET_S) & ICE_LG_ACT_GENERIC_OFFSET_M;

	/* Third action Marker value */
	act |= ICE_LG_ACT_GENERIC;
	act |= (sw_marker << ICE_LG_ACT_GENERIC_VALUE_S) &
		ICE_LG_ACT_GENERIC_VALUE_M;

	lg_act->pdata.lg_act.act[2] = cpu_to_le32(act);

	/* call the fill switch rule to fill the lookup Tx Rx structure */
	ice_fill_sw_rule(hw, &m_ent->fltr_info, rx_tx,
			 ice_aqc_opc_update_sw_rules);

	/* Update the action to point to the large action ID */
	rx_tx->pdata.lkup_tx_rx.act =
		cpu_to_le32(ICE_SINGLE_ACT_PTR |
			    ((l_id << ICE_SINGLE_ACT_PTR_VAL_S) &
			     ICE_SINGLE_ACT_PTR_VAL_M));

	/* Use the filter rule ID of the previously created rule with single
	 * act. Once the update happens, hardware will treat this as large
	 * action
	 */
	rx_tx->pdata.lkup_tx_rx.index =
		cpu_to_le16(m_ent->fltr_info.fltr_rule_id);

	status = ice_aq_sw_rules(hw, lg_act, rules_size, 2,
				 ice_aqc_opc_update_sw_rules, NULL);
	if (!status) {
		m_ent->lg_act_idx = l_id;
		m_ent->sw_marker_id = sw_marker;
	}

	devm_kfree(ice_hw_to_dev(hw), lg_act);
	return status;
}