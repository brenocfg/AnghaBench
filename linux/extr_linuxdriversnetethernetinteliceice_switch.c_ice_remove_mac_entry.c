#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ice_hw {int dummy; } ;
struct ice_fltr_mgmt_list_entry {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  vsi_id; } ;
struct TYPE_5__ {int /*<<< orphan*/ * mac_addr; } ;
struct TYPE_6__ {TYPE_1__ mac; } ;
struct TYPE_8__ {TYPE_3__ fwd_id; TYPE_2__ l_data; } ;
struct ice_fltr_list_entry {TYPE_4__ fltr_info; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int ICE_ERR_PARAM ; 
 struct ice_fltr_mgmt_list_entry* ice_find_mac_entry (struct ice_hw*,int /*<<< orphan*/ *) ; 
 int ice_handle_rem_vsi_list_mgmt (struct ice_hw*,int /*<<< orphan*/ ,struct ice_fltr_mgmt_list_entry*) ; 

__attribute__((used)) static enum ice_status
ice_remove_mac_entry(struct ice_hw *hw, struct ice_fltr_list_entry *f_entry)
{
	struct ice_fltr_mgmt_list_entry *m_entry;
	u16 vsi_id;
	u8 *add;

	add = &f_entry->fltr_info.l_data.mac.mac_addr[0];

	m_entry = ice_find_mac_entry(hw, add);
	if (!m_entry)
		return ICE_ERR_PARAM;

	vsi_id = f_entry->fltr_info.fwd_id.vsi_id;
	return ice_handle_rem_vsi_list_mgmt(hw, vsi_id, m_entry);
}