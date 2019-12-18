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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int mwl8k_cmd_update_mac_addr (struct ieee80211_hw*,struct ieee80211_vif*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int mwl8k_cmd_set_mac_addr(struct ieee80211_hw *hw,
				  struct ieee80211_vif *vif, u8 *mac)
{
	return mwl8k_cmd_update_mac_addr(hw, vif, mac, true);
}