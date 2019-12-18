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
struct ice_switch_info {int /*<<< orphan*/  vsi_list_map_head; } ;
struct ice_hw {struct ice_switch_info* switch_info; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ICE_ERR_NO_MEMORY ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct ice_switch_info* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 
 int ice_init_def_sw_recp (struct ice_hw*) ; 

__attribute__((used)) static enum ice_status ice_init_fltr_mgmt_struct(struct ice_hw *hw)
{
	struct ice_switch_info *sw;

	hw->switch_info = devm_kzalloc(ice_hw_to_dev(hw),
				       sizeof(*hw->switch_info), GFP_KERNEL);
	sw = hw->switch_info;

	if (!sw)
		return ICE_ERR_NO_MEMORY;

	INIT_LIST_HEAD(&sw->vsi_list_map_head);

	return ice_init_def_sw_recp(hw);
}