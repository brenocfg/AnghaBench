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
typedef  int u8 ;
typedef  void* u16 ;
struct ice_hw {TYPE_4__* port_info; } ;
struct TYPE_5__ {void* hw_vsi_id; } ;
struct ice_fltr_info {int flag; void* fltr_rule_id; void* src; int /*<<< orphan*/  src_id; TYPE_1__ fwd_id; int /*<<< orphan*/  fltr_act; int /*<<< orphan*/  lkup_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  index; } ;
struct TYPE_7__ {TYPE_2__ lkup_tx_rx; } ;
struct ice_aqc_sw_rules_elem {TYPE_3__ pdata; } ;
typedef  int /*<<< orphan*/  f_info ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
typedef  enum ice_adminq_opc { ____Placeholder_ice_adminq_opc } ice_adminq_opc ;
struct TYPE_8__ {void* dflt_rx_vsi_rule_id; void* dflt_rx_vsi_num; void* dflt_tx_vsi_rule_id; void* dflt_tx_vsi_num; void* lport; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* ICE_DFLT_VSI_INVAL ; 
 int ICE_ERR_NO_MEMORY ; 
 int ICE_ERR_PARAM ; 
 int ICE_FLTR_RX ; 
 int ICE_FLTR_TX ; 
 int ICE_FLTR_TX_RX ; 
 int /*<<< orphan*/  ICE_FWD_TO_VSI ; 
 void* ICE_INVAL_ACT ; 
 int /*<<< orphan*/  ICE_SRC_ID_LPORT ; 
 int /*<<< orphan*/  ICE_SRC_ID_VSI ; 
 int /*<<< orphan*/  ICE_SW_LKUP_DFLT ; 
 void* ICE_SW_RULE_RX_TX_ETH_HDR_SIZE ; 
 void* ICE_SW_RULE_RX_TX_NO_HDR_SIZE ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct ice_aqc_sw_rules_elem*) ; 
 struct ice_aqc_sw_rules_elem* devm_kzalloc (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int ice_aq_sw_rules (struct ice_hw*,struct ice_aqc_sw_rules_elem*,void*,int,int,int /*<<< orphan*/ *) ; 
 int ice_aqc_opc_add_sw_rules ; 
 int ice_aqc_opc_remove_sw_rules ; 
 int /*<<< orphan*/  ice_fill_sw_rule (struct ice_hw*,struct ice_fltr_info*,struct ice_aqc_sw_rules_elem*,int) ; 
 void* ice_get_hw_vsi_num (struct ice_hw*,void*) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_is_vsi_valid (struct ice_hw*,void*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ice_fltr_info*,int /*<<< orphan*/ ,int) ; 

enum ice_status
ice_cfg_dflt_vsi(struct ice_hw *hw, u16 vsi_handle, bool set, u8 direction)
{
	struct ice_aqc_sw_rules_elem *s_rule;
	struct ice_fltr_info f_info;
	enum ice_adminq_opc opcode;
	enum ice_status status;
	u16 s_rule_size;
	u16 hw_vsi_id;

	if (!ice_is_vsi_valid(hw, vsi_handle))
		return ICE_ERR_PARAM;
	hw_vsi_id = ice_get_hw_vsi_num(hw, vsi_handle);

	s_rule_size = set ? ICE_SW_RULE_RX_TX_ETH_HDR_SIZE :
			    ICE_SW_RULE_RX_TX_NO_HDR_SIZE;
	s_rule = devm_kzalloc(ice_hw_to_dev(hw), s_rule_size, GFP_KERNEL);
	if (!s_rule)
		return ICE_ERR_NO_MEMORY;

	memset(&f_info, 0, sizeof(f_info));

	f_info.lkup_type = ICE_SW_LKUP_DFLT;
	f_info.flag = direction;
	f_info.fltr_act = ICE_FWD_TO_VSI;
	f_info.fwd_id.hw_vsi_id = hw_vsi_id;

	if (f_info.flag & ICE_FLTR_RX) {
		f_info.src = hw->port_info->lport;
		f_info.src_id = ICE_SRC_ID_LPORT;
		if (!set)
			f_info.fltr_rule_id =
				hw->port_info->dflt_rx_vsi_rule_id;
	} else if (f_info.flag & ICE_FLTR_TX) {
		f_info.src_id = ICE_SRC_ID_VSI;
		f_info.src = hw_vsi_id;
		if (!set)
			f_info.fltr_rule_id =
				hw->port_info->dflt_tx_vsi_rule_id;
	}

	if (set)
		opcode = ice_aqc_opc_add_sw_rules;
	else
		opcode = ice_aqc_opc_remove_sw_rules;

	ice_fill_sw_rule(hw, &f_info, s_rule, opcode);

	status = ice_aq_sw_rules(hw, s_rule, s_rule_size, 1, opcode, NULL);
	if (status || !(f_info.flag & ICE_FLTR_TX_RX))
		goto out;
	if (set) {
		u16 index = le16_to_cpu(s_rule->pdata.lkup_tx_rx.index);

		if (f_info.flag & ICE_FLTR_TX) {
			hw->port_info->dflt_tx_vsi_num = hw_vsi_id;
			hw->port_info->dflt_tx_vsi_rule_id = index;
		} else if (f_info.flag & ICE_FLTR_RX) {
			hw->port_info->dflt_rx_vsi_num = hw_vsi_id;
			hw->port_info->dflt_rx_vsi_rule_id = index;
		}
	} else {
		if (f_info.flag & ICE_FLTR_TX) {
			hw->port_info->dflt_tx_vsi_num = ICE_DFLT_VSI_INVAL;
			hw->port_info->dflt_tx_vsi_rule_id = ICE_INVAL_ACT;
		} else if (f_info.flag & ICE_FLTR_RX) {
			hw->port_info->dflt_rx_vsi_num = ICE_DFLT_VSI_INVAL;
			hw->port_info->dflt_rx_vsi_rule_id = ICE_INVAL_ACT;
		}
	}

out:
	devm_kfree(ice_hw_to_dev(hw), s_rule);
	return status;
}