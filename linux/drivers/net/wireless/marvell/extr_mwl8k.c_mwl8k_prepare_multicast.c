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
typedef  unsigned long u64 ;
struct netdev_hw_addr_list {int dummy; } ;
struct mwl8k_cmd_pkt {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct mwl8k_cmd_pkt* __mwl8k_cmd_mac_multicast_adr (struct ieee80211_hw*,int /*<<< orphan*/ ,struct netdev_hw_addr_list*) ; 

__attribute__((used)) static u64 mwl8k_prepare_multicast(struct ieee80211_hw *hw,
				   struct netdev_hw_addr_list *mc_list)
{
	struct mwl8k_cmd_pkt *cmd;

	/*
	 * Synthesize and return a command packet that programs the
	 * hardware multicast address filter.  At this point we don't
	 * know whether FIF_ALLMULTI is being requested, but if it is,
	 * we'll end up throwing this packet away and creating a new
	 * one in mwl8k_configure_filter().
	 */
	cmd = __mwl8k_cmd_mac_multicast_adr(hw, 0, mc_list);

	return (unsigned long)cmd;
}