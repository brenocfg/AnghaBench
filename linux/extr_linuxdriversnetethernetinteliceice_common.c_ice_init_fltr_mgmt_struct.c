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
struct ice_switch_info {int /*<<< orphan*/  mac_vlan_list_head; int /*<<< orphan*/  mac_vlan_list_lock; int /*<<< orphan*/  promisc_list_head; int /*<<< orphan*/  promisc_list_lock; int /*<<< orphan*/  eth_m_list_head; int /*<<< orphan*/  eth_m_list_lock; int /*<<< orphan*/  vlan_list_head; int /*<<< orphan*/  vlan_list_lock; int /*<<< orphan*/  mac_list_head; int /*<<< orphan*/  mac_list_lock; int /*<<< orphan*/  vsi_list_map_head; } ;
struct ice_hw {struct ice_switch_info* switch_info; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ICE_ERR_NO_MEMORY ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct ice_switch_info* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum ice_status ice_init_fltr_mgmt_struct(struct ice_hw *hw)
{
	struct ice_switch_info *sw;

	hw->switch_info = devm_kzalloc(ice_hw_to_dev(hw),
				       sizeof(*hw->switch_info), GFP_KERNEL);
	sw = hw->switch_info;

	if (!sw)
		return ICE_ERR_NO_MEMORY;

	INIT_LIST_HEAD(&sw->vsi_list_map_head);

	mutex_init(&sw->mac_list_lock);
	INIT_LIST_HEAD(&sw->mac_list_head);

	mutex_init(&sw->vlan_list_lock);
	INIT_LIST_HEAD(&sw->vlan_list_head);

	mutex_init(&sw->eth_m_list_lock);
	INIT_LIST_HEAD(&sw->eth_m_list_head);

	mutex_init(&sw->promisc_list_lock);
	INIT_LIST_HEAD(&sw->promisc_list_head);

	mutex_init(&sw->mac_vlan_list_lock);
	INIT_LIST_HEAD(&sw->mac_vlan_list_head);

	return 0;
}