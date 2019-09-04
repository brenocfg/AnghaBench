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
struct TYPE_2__ {int /*<<< orphan*/  set_vfta; int /*<<< orphan*/  set_uc_addr; int /*<<< orphan*/  read_mac_addr; int /*<<< orphan*/  rar_set; int /*<<< orphan*/  update_mc_addr_list; int /*<<< orphan*/  get_link_up_info; int /*<<< orphan*/  check_for_link; int /*<<< orphan*/  init_hw; int /*<<< orphan*/  reset_hw; } ;
struct e1000_mac_info {int mta_reg_count; int rar_entry_count; TYPE_1__ ops; } ;
struct e1000_hw {struct e1000_mac_info mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  e1000_check_for_link_vf ; 
 int /*<<< orphan*/  e1000_get_link_up_info_vf ; 
 int /*<<< orphan*/  e1000_init_hw_vf ; 
 int /*<<< orphan*/  e1000_rar_set_vf ; 
 int /*<<< orphan*/  e1000_read_mac_addr_vf ; 
 int /*<<< orphan*/  e1000_reset_hw_vf ; 
 int /*<<< orphan*/  e1000_set_uc_addr_vf ; 
 int /*<<< orphan*/  e1000_set_vfta_vf ; 
 int /*<<< orphan*/  e1000_update_mc_addr_list_vf ; 

__attribute__((used)) static s32 e1000_init_mac_params_vf(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;

	/* VF's have no MTA Registers - PF feature only */
	mac->mta_reg_count = 128;
	/* VF's have no access to RAR entries  */
	mac->rar_entry_count = 1;

	/* Function pointers */
	/* reset */
	mac->ops.reset_hw = e1000_reset_hw_vf;
	/* hw initialization */
	mac->ops.init_hw = e1000_init_hw_vf;
	/* check for link */
	mac->ops.check_for_link = e1000_check_for_link_vf;
	/* link info */
	mac->ops.get_link_up_info = e1000_get_link_up_info_vf;
	/* multicast address update */
	mac->ops.update_mc_addr_list = e1000_update_mc_addr_list_vf;
	/* set mac address */
	mac->ops.rar_set = e1000_rar_set_vf;
	/* read mac address */
	mac->ops.read_mac_addr = e1000_read_mac_addr_vf;
	/* set mac filter */
	mac->ops.set_uc_addr = e1000_set_uc_addr_vf;
	/* set vlan filter table array */
	mac->ops.set_vfta = e1000_set_vfta_vf;

	return E1000_SUCCESS;
}