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
typedef  int /*<<< orphan*/  u16 ;
struct ice_sched_node {int /*<<< orphan*/  info; int /*<<< orphan*/  children; } ;
struct ice_port_info {struct ice_sched_node* root; struct ice_hw* hw; } ;
struct ice_hw {TYPE_1__* layer_info; } ;
struct ice_aqc_txsched_elem_data {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_2__ {int /*<<< orphan*/  max_children; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ICE_ERR_NO_MEMORY ; 
 int ICE_ERR_PARAM ; 
 int /*<<< orphan*/  devm_kcalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct ice_sched_node*) ; 
 struct ice_sched_node* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ice_aqc_txsched_elem_data*,int) ; 

__attribute__((used)) static enum ice_status
ice_sched_add_root_node(struct ice_port_info *pi,
			struct ice_aqc_txsched_elem_data *info)
{
	struct ice_sched_node *root;
	struct ice_hw *hw;
	u16 max_children;

	if (!pi)
		return ICE_ERR_PARAM;

	hw = pi->hw;

	root = devm_kzalloc(ice_hw_to_dev(hw), sizeof(*root), GFP_KERNEL);
	if (!root)
		return ICE_ERR_NO_MEMORY;

	max_children = le16_to_cpu(hw->layer_info[0].max_children);
	root->children = devm_kcalloc(ice_hw_to_dev(hw), max_children,
				      sizeof(*root), GFP_KERNEL);
	if (!root->children) {
		devm_kfree(ice_hw_to_dev(hw), root);
		return ICE_ERR_NO_MEMORY;
	}

	memcpy(&root->info, info, sizeof(*info));
	pi->root = root;
	return 0;
}