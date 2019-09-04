#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct ice_hw_common_caps {scalar_t__ max_mtu; scalar_t__ msix_vector_first_id; scalar_t__ num_msix_vectors; scalar_t__ txq_first_id; scalar_t__ num_txq; scalar_t__ rxq_first_id; scalar_t__ num_rxq; scalar_t__ rss_table_entry_width; scalar_t__ rss_table_size; } ;
struct ice_hw_func_caps {scalar_t__ guaranteed_num_vsi; struct ice_hw_common_caps common_cap; } ;
struct ice_hw_dev_caps {scalar_t__ num_vsi_allocd_to_host; struct ice_hw_common_caps common_cap; } ;
struct ice_hw {struct ice_hw_func_caps func_caps; struct ice_hw_dev_caps dev_caps; } ;
struct ice_aqc_list_caps_elem {int /*<<< orphan*/  cap; int /*<<< orphan*/  number; int /*<<< orphan*/  phys_id; int /*<<< orphan*/  logical_id; } ;
typedef  enum ice_adminq_opc { ____Placeholder_ice_adminq_opc } ice_adminq_opc ;

/* Variables and functions */
#define  ICE_AQC_CAPS_MAX_MTU 133 
#define  ICE_AQC_CAPS_MSIX 132 
#define  ICE_AQC_CAPS_RSS 131 
#define  ICE_AQC_CAPS_RXQS 130 
#define  ICE_AQC_CAPS_TXQS 129 
#define  ICE_AQC_CAPS_VSI 128 
 int /*<<< orphan*/  ICE_DBG_INIT ; 
 int ice_aqc_opc_list_dev_caps ; 
 int ice_aqc_opc_list_func_caps ; 
 int /*<<< orphan*/  ice_debug (struct ice_hw*,int /*<<< orphan*/ ,char*,...) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ice_parse_caps(struct ice_hw *hw, void *buf, u32 cap_count,
	       enum ice_adminq_opc opc)
{
	struct ice_aqc_list_caps_elem *cap_resp;
	struct ice_hw_func_caps *func_p = NULL;
	struct ice_hw_dev_caps *dev_p = NULL;
	struct ice_hw_common_caps *caps;
	u32 i;

	if (!buf)
		return;

	cap_resp = (struct ice_aqc_list_caps_elem *)buf;

	if (opc == ice_aqc_opc_list_dev_caps) {
		dev_p = &hw->dev_caps;
		caps = &dev_p->common_cap;
	} else if (opc == ice_aqc_opc_list_func_caps) {
		func_p = &hw->func_caps;
		caps = &func_p->common_cap;
	} else {
		ice_debug(hw, ICE_DBG_INIT, "wrong opcode\n");
		return;
	}

	for (i = 0; caps && i < cap_count; i++, cap_resp++) {
		u32 logical_id = le32_to_cpu(cap_resp->logical_id);
		u32 phys_id = le32_to_cpu(cap_resp->phys_id);
		u32 number = le32_to_cpu(cap_resp->number);
		u16 cap = le16_to_cpu(cap_resp->cap);

		switch (cap) {
		case ICE_AQC_CAPS_VSI:
			if (dev_p) {
				dev_p->num_vsi_allocd_to_host = number;
				ice_debug(hw, ICE_DBG_INIT,
					  "HW caps: Dev.VSI cnt = %d\n",
					  dev_p->num_vsi_allocd_to_host);
			} else if (func_p) {
				func_p->guaranteed_num_vsi = number;
				ice_debug(hw, ICE_DBG_INIT,
					  "HW caps: Func.VSI cnt = %d\n",
					  func_p->guaranteed_num_vsi);
			}
			break;
		case ICE_AQC_CAPS_RSS:
			caps->rss_table_size = number;
			caps->rss_table_entry_width = logical_id;
			ice_debug(hw, ICE_DBG_INIT,
				  "HW caps: RSS table size = %d\n",
				  caps->rss_table_size);
			ice_debug(hw, ICE_DBG_INIT,
				  "HW caps: RSS table width = %d\n",
				  caps->rss_table_entry_width);
			break;
		case ICE_AQC_CAPS_RXQS:
			caps->num_rxq = number;
			caps->rxq_first_id = phys_id;
			ice_debug(hw, ICE_DBG_INIT,
				  "HW caps: Num Rx Qs = %d\n", caps->num_rxq);
			ice_debug(hw, ICE_DBG_INIT,
				  "HW caps: Rx first queue ID = %d\n",
				  caps->rxq_first_id);
			break;
		case ICE_AQC_CAPS_TXQS:
			caps->num_txq = number;
			caps->txq_first_id = phys_id;
			ice_debug(hw, ICE_DBG_INIT,
				  "HW caps: Num Tx Qs = %d\n", caps->num_txq);
			ice_debug(hw, ICE_DBG_INIT,
				  "HW caps: Tx first queue ID = %d\n",
				  caps->txq_first_id);
			break;
		case ICE_AQC_CAPS_MSIX:
			caps->num_msix_vectors = number;
			caps->msix_vector_first_id = phys_id;
			ice_debug(hw, ICE_DBG_INIT,
				  "HW caps: MSIX vector count = %d\n",
				  caps->num_msix_vectors);
			ice_debug(hw, ICE_DBG_INIT,
				  "HW caps: MSIX first vector index = %d\n",
				  caps->msix_vector_first_id);
			break;
		case ICE_AQC_CAPS_MAX_MTU:
			caps->max_mtu = number;
			if (dev_p)
				ice_debug(hw, ICE_DBG_INIT,
					  "HW caps: Dev.MaxMTU = %d\n",
					  caps->max_mtu);
			else if (func_p)
				ice_debug(hw, ICE_DBG_INIT,
					  "HW caps: func.MaxMTU = %d\n",
					  caps->max_mtu);
			break;
		default:
			ice_debug(hw, ICE_DBG_INIT,
				  "HW caps: Unknown capability[%d]: 0x%x\n", i,
				  cap);
			break;
		}
	}
}