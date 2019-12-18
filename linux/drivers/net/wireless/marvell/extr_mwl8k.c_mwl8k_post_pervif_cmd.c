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
struct mwl8k_cmd_pkt {int /*<<< orphan*/  macid; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  macid; } ;

/* Variables and functions */
 TYPE_1__* MWL8K_VIF (struct ieee80211_vif*) ; 
 int mwl8k_post_cmd (struct ieee80211_hw*,struct mwl8k_cmd_pkt*) ; 

__attribute__((used)) static int mwl8k_post_pervif_cmd(struct ieee80211_hw *hw,
				 struct ieee80211_vif *vif,
				 struct mwl8k_cmd_pkt *cmd)
{
	if (vif != NULL)
		cmd->macid = MWL8K_VIF(vif)->macid;
	return mwl8k_post_cmd(hw, cmd);
}