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
typedef  int u16 ;
struct ice_vsi_list_map_info {int vsi_list_id; int ref_cnt; int /*<<< orphan*/  list_entry; int /*<<< orphan*/  vsi_map; } ;
struct ice_switch_info {int /*<<< orphan*/  vsi_list_map_head; } ;
struct ice_hw {struct ice_switch_info* switch_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ice_vsi_list_map_info* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ice_vsi_list_map_info *
ice_create_vsi_list_map(struct ice_hw *hw, u16 *vsi_handle_arr, u16 num_vsi,
			u16 vsi_list_id)
{
	struct ice_switch_info *sw = hw->switch_info;
	struct ice_vsi_list_map_info *v_map;
	int i;

	v_map = devm_kcalloc(ice_hw_to_dev(hw), 1, sizeof(*v_map), GFP_KERNEL);
	if (!v_map)
		return NULL;

	v_map->vsi_list_id = vsi_list_id;
	v_map->ref_cnt = 1;
	for (i = 0; i < num_vsi; i++)
		set_bit(vsi_handle_arr[i], v_map->vsi_map);

	list_add(&v_map->list_entry, &sw->vsi_list_map_head);
	return v_map;
}