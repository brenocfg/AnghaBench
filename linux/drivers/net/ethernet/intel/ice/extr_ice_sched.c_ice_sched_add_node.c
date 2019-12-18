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
typedef  size_t u8 ;
struct ice_sched_node {int in_use; size_t tx_sched_layer; int /*<<< orphan*/  info; int /*<<< orphan*/  num_children; struct ice_sched_node** children; struct ice_sched_node* parent; } ;
struct ice_port_info {int /*<<< orphan*/  root; struct ice_hw* hw; } ;
struct ice_hw {scalar_t__* max_children; } ;
struct ice_aqc_txsched_elem_data {int /*<<< orphan*/  node_teid; int /*<<< orphan*/  parent_teid; } ;
struct ice_aqc_get_elem {int /*<<< orphan*/ * generic; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICE_DBG_SCHED ; 
 int ICE_ERR_NO_MEMORY ; 
 int ICE_ERR_PARAM ; 
 struct ice_sched_node** devm_kcalloc (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct ice_sched_node*) ; 
 struct ice_sched_node* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_debug (struct ice_hw*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 
 struct ice_sched_node* ice_sched_find_node_by_teid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ice_sched_query_elem (struct ice_hw*,int /*<<< orphan*/ ,struct ice_aqc_get_elem*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

enum ice_status
ice_sched_add_node(struct ice_port_info *pi, u8 layer,
		   struct ice_aqc_txsched_elem_data *info)
{
	struct ice_sched_node *parent;
	struct ice_aqc_get_elem elem;
	struct ice_sched_node *node;
	enum ice_status status;
	struct ice_hw *hw;

	if (!pi)
		return ICE_ERR_PARAM;

	hw = pi->hw;

	/* A valid parent node should be there */
	parent = ice_sched_find_node_by_teid(pi->root,
					     le32_to_cpu(info->parent_teid));
	if (!parent) {
		ice_debug(hw, ICE_DBG_SCHED,
			  "Parent Node not found for parent_teid=0x%x\n",
			  le32_to_cpu(info->parent_teid));
		return ICE_ERR_PARAM;
	}

	/* query the current node information from FW  before additing it
	 * to the SW DB
	 */
	status = ice_sched_query_elem(hw, le32_to_cpu(info->node_teid), &elem);
	if (status)
		return status;

	node = devm_kzalloc(ice_hw_to_dev(hw), sizeof(*node), GFP_KERNEL);
	if (!node)
		return ICE_ERR_NO_MEMORY;
	if (hw->max_children[layer]) {
		/* coverity[suspicious_sizeof] */
		node->children = devm_kcalloc(ice_hw_to_dev(hw),
					      hw->max_children[layer],
					      sizeof(*node), GFP_KERNEL);
		if (!node->children) {
			devm_kfree(ice_hw_to_dev(hw), node);
			return ICE_ERR_NO_MEMORY;
		}
	}

	node->in_use = true;
	node->parent = parent;
	node->tx_sched_layer = layer;
	parent->children[parent->num_children++] = node;
	memcpy(&node->info, &elem.generic[0], sizeof(node->info));
	return 0;
}