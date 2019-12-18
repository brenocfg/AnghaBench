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
struct TYPE_2__ {int match_flags; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; int /*<<< orphan*/  vlan_tci; } ;
struct igb_nfc_filter {int /*<<< orphan*/  action; TYPE_1__ filter; int /*<<< orphan*/  etype_reg_index; } ;
struct igb_adapter {int dummy; } ;

/* Variables and functions */
 int IGB_FILTER_FLAG_DST_MAC_ADDR ; 
 int IGB_FILTER_FLAG_ETHER_TYPE ; 
 int IGB_FILTER_FLAG_SRC_MAC_ADDR ; 
 int IGB_FILTER_FLAG_VLAN_TCI ; 
 int /*<<< orphan*/  IGB_MAC_STATE_SRC_ADDR ; 
 int /*<<< orphan*/  igb_clear_etype_filter_regs (struct igb_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igb_clear_vlan_prio_filter (struct igb_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igb_del_mac_steering_filter (struct igb_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

int igb_erase_filter(struct igb_adapter *adapter, struct igb_nfc_filter *input)
{
	if (input->filter.match_flags & IGB_FILTER_FLAG_ETHER_TYPE)
		igb_clear_etype_filter_regs(adapter,
					    input->etype_reg_index);

	if (input->filter.match_flags & IGB_FILTER_FLAG_VLAN_TCI)
		igb_clear_vlan_prio_filter(adapter,
					   ntohs(input->filter.vlan_tci));

	if (input->filter.match_flags & IGB_FILTER_FLAG_SRC_MAC_ADDR)
		igb_del_mac_steering_filter(adapter, input->filter.src_addr,
					    input->action,
					    IGB_MAC_STATE_SRC_ADDR);

	if (input->filter.match_flags & IGB_FILTER_FLAG_DST_MAC_ADDR)
		igb_del_mac_steering_filter(adapter, input->filter.dst_addr,
					    input->action, 0);

	return 0;
}