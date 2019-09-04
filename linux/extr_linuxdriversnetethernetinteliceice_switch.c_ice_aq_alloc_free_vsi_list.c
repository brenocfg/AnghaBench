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
typedef  int u16 ;
struct ice_hw {int dummy; } ;
struct TYPE_2__ {void* sw_resp; } ;
struct ice_aqc_res_elem {TYPE_1__ e; } ;
struct ice_aqc_alloc_free_res_elem {struct ice_aqc_res_elem* elem; void* res_type; void* num_elems; } ;
typedef  enum ice_sw_lkup_type { ____Placeholder_ice_sw_lkup_type } ice_sw_lkup_type ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
typedef  enum ice_adminq_opc { ____Placeholder_ice_adminq_opc } ice_adminq_opc ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ICE_AQC_RES_TYPE_VSI_LIST_PRUNE ; 
 int ICE_AQC_RES_TYPE_VSI_LIST_REP ; 
 int ICE_ERR_NO_MEMORY ; 
 int ICE_ERR_PARAM ; 
 int ICE_SW_LKUP_ETHERTYPE ; 
 int ICE_SW_LKUP_ETHERTYPE_MAC ; 
 int ICE_SW_LKUP_MAC ; 
 int ICE_SW_LKUP_MAC_VLAN ; 
 int ICE_SW_LKUP_PROMISC ; 
 int ICE_SW_LKUP_PROMISC_VLAN ; 
 int ICE_SW_LKUP_VLAN ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct ice_aqc_alloc_free_res_elem*) ; 
 struct ice_aqc_alloc_free_res_elem* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ice_aq_alloc_free_res (struct ice_hw*,int,struct ice_aqc_alloc_free_res_elem*,int,int,int /*<<< orphan*/ *) ; 
 int ice_aqc_opc_alloc_res ; 
 int ice_aqc_opc_free_res ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 
 int le16_to_cpu (void*) ; 

__attribute__((used)) static enum ice_status
ice_aq_alloc_free_vsi_list(struct ice_hw *hw, u16 *vsi_list_id,
			   enum ice_sw_lkup_type lkup_type,
			   enum ice_adminq_opc opc)
{
	struct ice_aqc_alloc_free_res_elem *sw_buf;
	struct ice_aqc_res_elem *vsi_ele;
	enum ice_status status;
	u16 buf_len;

	buf_len = sizeof(*sw_buf);
	sw_buf = devm_kzalloc(ice_hw_to_dev(hw), buf_len, GFP_KERNEL);
	if (!sw_buf)
		return ICE_ERR_NO_MEMORY;
	sw_buf->num_elems = cpu_to_le16(1);

	if (lkup_type == ICE_SW_LKUP_MAC ||
	    lkup_type == ICE_SW_LKUP_MAC_VLAN ||
	    lkup_type == ICE_SW_LKUP_ETHERTYPE ||
	    lkup_type == ICE_SW_LKUP_ETHERTYPE_MAC ||
	    lkup_type == ICE_SW_LKUP_PROMISC ||
	    lkup_type == ICE_SW_LKUP_PROMISC_VLAN) {
		sw_buf->res_type = cpu_to_le16(ICE_AQC_RES_TYPE_VSI_LIST_REP);
	} else if (lkup_type == ICE_SW_LKUP_VLAN) {
		sw_buf->res_type =
			cpu_to_le16(ICE_AQC_RES_TYPE_VSI_LIST_PRUNE);
	} else {
		status = ICE_ERR_PARAM;
		goto ice_aq_alloc_free_vsi_list_exit;
	}

	if (opc == ice_aqc_opc_free_res)
		sw_buf->elem[0].e.sw_resp = cpu_to_le16(*vsi_list_id);

	status = ice_aq_alloc_free_res(hw, 1, sw_buf, buf_len, opc, NULL);
	if (status)
		goto ice_aq_alloc_free_vsi_list_exit;

	if (opc == ice_aqc_opc_alloc_res) {
		vsi_ele = &sw_buf->elem[0];
		*vsi_list_id = le16_to_cpu(vsi_ele->e.sw_resp);
	}

ice_aq_alloc_free_vsi_list_exit:
	devm_kfree(ice_hw_to_dev(hw), sw_buf);
	return status;
}