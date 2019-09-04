#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_8__ {int /*<<< orphan*/  node_teid; } ;
struct ice_sched_node {struct ice_sched_node* sibling; int /*<<< orphan*/  tc_num; TYPE_2__ info; } ;
struct ice_port_info {struct ice_hw* hw; } ;
struct ice_hw {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  num_elems; int /*<<< orphan*/  parent_teid; } ;
struct ice_aqc_add_elem {TYPE_6__* generic; TYPE_1__ hdr; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_10__ {void* bw_profile_idx; } ;
struct TYPE_9__ {void* bw_profile_idx; } ;
struct TYPE_11__ {int valid_sections; TYPE_4__ eir_bw; TYPE_3__ cir_bw; scalar_t__ generic; int /*<<< orphan*/  elem_type; } ;
struct TYPE_12__ {int /*<<< orphan*/  node_teid; TYPE_5__ data; int /*<<< orphan*/  parent_teid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICE_AQC_ELEM_TYPE_SE_GENERIC ; 
 int ICE_AQC_ELEM_VALID_CIR ; 
 int ICE_AQC_ELEM_VALID_EIR ; 
 int ICE_AQC_ELEM_VALID_GENERIC ; 
 int /*<<< orphan*/  ICE_DBG_SCHED ; 
 int ICE_ERR_CFG ; 
 int ICE_ERR_NO_MEMORY ; 
 void* ICE_SCHED_DFLT_RL_PROF_ID ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct ice_aqc_add_elem*) ; 
 struct ice_aqc_add_elem* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ice_aq_add_sched_elems (struct ice_hw*,int,struct ice_aqc_add_elem*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_debug (struct ice_hw*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 
 int ice_sched_add_node (struct ice_port_info*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 struct ice_sched_node* ice_sched_find_node_by_teid (struct ice_sched_node*,int) ; 
 struct ice_sched_node* ice_sched_get_first_node (struct ice_hw*,struct ice_sched_node*,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

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
	u16 buf_size;
	u32 teid;

	buf_size = sizeof(*buf) + sizeof(*buf->generic) * (num_nodes - 1);
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
			ICE_SCHED_DFLT_RL_PROF_ID;
		buf->generic[i].data.eir_bw.bw_profile_idx =
			ICE_SCHED_DFLT_RL_PROF_ID;
	}

	status = ice_aq_add_sched_elems(hw, 1, buf, buf_size,
					&num_groups_added, NULL);
	if (status || num_groups_added != 1) {
		ice_debug(hw, ICE_DBG_SCHED, "add elements failed\n");
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
		prev = ice_sched_get_first_node(hw, tc_node, layer);

		if (prev && prev != new_node) {
			while (prev->sibling)
				prev = prev->sibling;
			prev->sibling = new_node;
		}

		if (i == 0)
			*first_node_teid = teid;
	}

	devm_kfree(ice_hw_to_dev(hw), buf);
	return status;
}