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
typedef  int /*<<< orphan*/  u16 ;
struct ice_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_SW_LKUP_DFLT ; 
 int /*<<< orphan*/  ICE_SW_LKUP_ETHERTYPE ; 
 int /*<<< orphan*/  ICE_SW_LKUP_ETHERTYPE_MAC ; 
 int /*<<< orphan*/  ICE_SW_LKUP_MAC ; 
 int /*<<< orphan*/  ICE_SW_LKUP_MAC_VLAN ; 
 int /*<<< orphan*/  ICE_SW_LKUP_PROMISC ; 
 int /*<<< orphan*/  ICE_SW_LKUP_PROMISC_VLAN ; 
 int /*<<< orphan*/  ICE_SW_LKUP_VLAN ; 
 int /*<<< orphan*/  ice_remove_vsi_lkup_fltr (struct ice_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ice_remove_vsi_fltr(struct ice_hw *hw, u16 vsi_handle)
{
	ice_remove_vsi_lkup_fltr(hw, vsi_handle, ICE_SW_LKUP_MAC);
	ice_remove_vsi_lkup_fltr(hw, vsi_handle, ICE_SW_LKUP_MAC_VLAN);
	ice_remove_vsi_lkup_fltr(hw, vsi_handle, ICE_SW_LKUP_PROMISC);
	ice_remove_vsi_lkup_fltr(hw, vsi_handle, ICE_SW_LKUP_VLAN);
	ice_remove_vsi_lkup_fltr(hw, vsi_handle, ICE_SW_LKUP_DFLT);
	ice_remove_vsi_lkup_fltr(hw, vsi_handle, ICE_SW_LKUP_ETHERTYPE);
	ice_remove_vsi_lkup_fltr(hw, vsi_handle, ICE_SW_LKUP_ETHERTYPE_MAC);
	ice_remove_vsi_lkup_fltr(hw, vsi_handle, ICE_SW_LKUP_PROMISC_VLAN);
}