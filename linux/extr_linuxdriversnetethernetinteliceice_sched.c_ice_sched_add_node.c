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
typedef  size_t u8 ;
typedef  scalar_t__ u16 ;
struct ice_sched_node {int in_use; size_t tx_sched_layer; int /*<<< orphan*/  info; int /*<<< orphan*/  num_children; struct ice_sched_node** children; struct ice_sched_node* parent; } ;
struct ice_port_info {int /*<<< orphan*/  root; struct ice_hw* hw; } ;
struct ice_hw {TYPE_1__* layer_info; } ;
struct ice_aqc_txsched_elem_data {int /*<<< orphan*/  parent_teid; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_2__ {int /*<<< orphan*/  max_children; } ;

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
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ice_aqc_txsched_elem_data*,int) ; 

enum ice_status
ice_sched_add_node(struct ice_port_info *pi, u8 layer,
		   struct ice_aqc_txsched_elem_data *info)
{
	struct ice_sched_node *parent;
	struct ice_sched_node *node;
	struct ice_hw *hw;
	u16 max_children;

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

	node = devm_kzalloc(ice_hw_to_dev(hw), sizeof(*node), GFP_KERNEL);
	if (!node)
		return ICE_ERR_NO_MEMORY;
	max_children = le16_to_cpu(hw->layer_info[layer].max_children);
	if (max_children) {
		node->children = devm_kcalloc(ice_hw_to_dev(hw), max_children,
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
	memcpy(&node->info, info, sizeof(*info));
	return 0;
}