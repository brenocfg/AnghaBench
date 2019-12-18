#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_9__ {int /*<<< orphan*/  node_teid; } ;
struct ice_sched_node {size_t tc_num; struct ice_sched_node* sibling; TYPE_2__ info; } ;
struct ice_port_info {struct ice_sched_node*** sib_head; struct ice_hw* hw; } ;
struct TYPE_13__ {int sq_last_status; } ;
struct ice_hw {TYPE_6__ adminq; } ;
struct TYPE_8__ {void* num_elems; int /*<<< orphan*/  parent_teid; } ;
struct ice_aqc_add_elem {TYPE_7__* generic; TYPE_1__ hdr; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_11__ {void* bw_alloc; void* bw_profile_idx; } ;
struct TYPE_10__ {void* bw_alloc; void* bw_profile_idx; } ;
struct TYPE_12__ {int valid_sections; TYPE_4__ eir_bw; TYPE_3__ cir_bw; scalar_t__ generic; int /*<<< orphan*/  elem_type; } ;
struct TYPE_14__ {int /*<<< orphan*/  node_teid; TYPE_5__ data; int /*<<< orphan*/  parent_teid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICE_AQC_ELEM_TYPE_SE_GENERIC ; 
 int ICE_AQC_ELEM_VALID_CIR ; 
 int ICE_AQC_ELEM_VALID_EIR ; 
 int ICE_AQC_ELEM_VALID_GENERIC ; 
 int /*<<< orphan*/  ICE_DBG_SCHED ; 
 int ICE_ERR_CFG ; 
 int ICE_ERR_NO_MEMORY ; 
 int ICE_SCHED_DFLT_BW_WT ; 
 int ICE_SCHED_DFLT_RL_PROF_ID ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct ice_aqc_add_elem*) ; 
 struct ice_aqc_add_elem* devm_kzalloc (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic ; 
 int ice_aq_add_sched_elems (struct ice_hw*,int,struct ice_aqc_add_elem*,size_t,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_debug (struct ice_hw*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 
 int ice_sched_add_node (struct ice_port_info*,size_t,TYPE_7__*) ; 
 struct ice_sched_node* ice_sched_find_node_by_teid (struct ice_sched_node*,int) ; 
 struct ice_sched_node* ice_sched_get_first_node (struct ice_port_info*,struct ice_sched_node*,size_t) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 size_t struct_size (struct ice_aqc_add_elem*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum ice_status
ice_sched_add_elems(struct ice_port_info *pi, struct ice_sched_node *tc_node,
		    struct ice_sched_node *parent, u8 layer, u16 num_nodes,
		    u16 *num_nodes_added, u32 *first_node_teid)
{
	struct ice_sched_node *prev, *new_node;
	struct ice_aqc_add_elem *buf;
	u16 i, num_groups_added = 0;
	enum ice_status status = 0;
	struct ice_hw *hw = pi->hw;
	size_t buf_size;
	u32 teid;

	buf_size = struct_size(buf, generic, num_nodes - 1);
	buf = devm_kzalloc(ice_hw_to_dev(hw), buf_size, GFP_KERNEL);
	if (!buf)
		return ICE_ERR_NO_MEMORY;

	buf->hdr.parent_teid = parent->info.node_teid;
	buf->hdr.num_elems = cpu_to_le16(num_nodes);
	for (i = 0; i < num_nodes; i++) {
		buf->generic[i].parent_teid = parent->info.node_teid;
		buf->generic[i].data.elem_type = ICE_AQC_ELEM_TYPE_SE_GENERIC;
		buf->generic[i].data.valid_sections =
			ICE_AQC_ELEM_VALID_GENERIC | ICE_AQC_ELEM_VALID_CIR |
			ICE_AQC_ELEM_VALID_EIR;
		buf->generic[i].data.generic = 0;
		buf->generic[i].data.cir_bw.bw_profile_idx =
			cpu_to_le16(ICE_SCHED_DFLT_RL_PROF_ID);
		buf->generic[i].data.cir_bw.bw_alloc =
			cpu_to_le16(ICE_SCHED_DFLT_BW_WT);
		buf->generic[i].data.eir_bw.bw_profile_idx =
			cpu_to_le16(ICE_SCHED_DFLT_RL_PROF_ID);
		buf->generic[i].data.eir_bw.bw_alloc =
			cpu_to_le16(ICE_SCHED_DFLT_BW_WT);
	}

	status = ice_aq_add_sched_elems(hw, 1, buf, buf_size,
					&num_groups_added, NULL);
	if (status || num_groups_added != 1) {
		ice_debug(hw, ICE_DBG_SCHED, "add node failed FW Error %d\n",
			  hw->adminq.sq_last_status);
		devm_kfree(ice_hw_to_dev(hw), buf);
		return ICE_ERR_CFG;
	}

	*num_nodes_added = num_nodes;
	/* add nodes to the SW DB */
	for (i = 0; i < num_nodes; i++) {
		status = ice_sched_add_node(pi, layer, &buf->generic[i]);
		if (status) {
			ice_debug(hw, ICE_DBG_SCHED,
				  "add nodes in SW DB failed status =%d\n",
				  status);
			break;
		}

		teid = le32_to_cpu(buf->generic[i].node_teid);
		new_node = ice_sched_find_node_by_teid(parent, teid);
		if (!new_node) {
			ice_debug(hw, ICE_DBG_SCHED,
				  "Node is missing for teid =%d\n", teid);
			break;
		}

		new_node->sibling = NULL;
		new_node->tc_num = tc_node->tc_num;

		/* add it to previous node sibling pointer */
		/* Note: siblings are not linked across branches */
		prev = ice_sched_get_first_node(pi, tc_node, layer);
		if (prev && prev != new_node) {
			while (prev->sibling)
				prev = prev->sibling;
			prev->sibling = new_node;
		}

		/* initialize the sibling head */
		if (!pi->sib_head[tc_node->tc_num][layer])
			pi->sib_head[tc_node->tc_num][layer] = new_node;

		if (i == 0)
			*first_node_teid = teid;
	}

	devm_kfree(ice_hw_to_dev(hw), buf);
	return status;
}