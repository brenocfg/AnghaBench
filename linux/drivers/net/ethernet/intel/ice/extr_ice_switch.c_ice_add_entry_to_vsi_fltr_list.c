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
struct list_head {int dummy; } ;
struct ice_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_vsi_id; } ;
struct ice_fltr_info {TYPE_1__ fwd_id; int /*<<< orphan*/  vsi_handle; int /*<<< orphan*/  fltr_act; } ;
struct ice_fltr_list_entry {int /*<<< orphan*/  list_entry; struct ice_fltr_info fltr_info; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ICE_ERR_NO_MEMORY ; 
 int /*<<< orphan*/  ICE_FWD_TO_VSI ; 
 struct ice_fltr_list_entry* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_get_hw_vsi_num (struct ice_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static enum ice_status
ice_add_entry_to_vsi_fltr_list(struct ice_hw *hw, u16 vsi_handle,
			       struct list_head *vsi_list_head,
			       struct ice_fltr_info *fi)
{
	struct ice_fltr_list_entry *tmp;

	/* this memory is freed up in the caller function
	 * once filters for this VSI are removed
	 */
	tmp = devm_kzalloc(ice_hw_to_dev(hw), sizeof(*tmp), GFP_KERNEL);
	if (!tmp)
		return ICE_ERR_NO_MEMORY;

	tmp->fltr_info = *fi;

	/* Overwrite these fields to indicate which VSI to remove filter from,
	 * so find and remove logic can extract the information from the
	 * list entries. Note that original entries will still have proper
	 * values.
	 */
	tmp->fltr_info.fltr_act = ICE_FWD_TO_VSI;
	tmp->fltr_info.vsi_handle = vsi_handle;
	tmp->fltr_info.fwd_id.hw_vsi_id = ice_get_hw_vsi_num(hw, vsi_handle);

	list_add(&tmp->list_entry, vsi_list_head);

	return 0;
}