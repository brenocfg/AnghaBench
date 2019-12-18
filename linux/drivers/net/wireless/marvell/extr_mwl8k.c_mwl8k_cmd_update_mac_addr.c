#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct mwl8k_vif {scalar_t__ macid; } ;
struct mwl8k_priv {scalar_t__ ap_fw; int /*<<< orphan*/  ap_macids_supported; int /*<<< orphan*/  sta_macids_supported; } ;
struct TYPE_4__ {void* length; void* code; } ;
struct TYPE_3__ {int /*<<< orphan*/  mac_addr; void* mac_type; } ;
struct mwl8k_cmd_update_mac_addr {TYPE_2__ header; int /*<<< orphan*/  mac_addr; TYPE_1__ mbss; } ;
struct ieee80211_vif {scalar_t__ type; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MWL8K_CMD_DEL_MAC_ADDR ; 
 int MWL8K_CMD_SET_MAC_ADDR ; 
 int MWL8K_MAC_TYPE_PRIMARY_AP ; 
 int MWL8K_MAC_TYPE_PRIMARY_CLIENT ; 
 int MWL8K_MAC_TYPE_SECONDARY_AP ; 
 int MWL8K_MAC_TYPE_SECONDARY_CLIENT ; 
 struct mwl8k_vif* MWL8K_VIF (struct ieee80211_vif*) ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 void* cpu_to_le16 (int) ; 
 scalar_t__ ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mwl8k_cmd_update_mac_addr*) ; 
 struct mwl8k_cmd_update_mac_addr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mwl8k_post_pervif_cmd (struct ieee80211_hw*,struct ieee80211_vif*,TYPE_2__*) ; 

__attribute__((used)) static int mwl8k_cmd_update_mac_addr(struct ieee80211_hw *hw,
				  struct ieee80211_vif *vif, u8 *mac, bool set)
{
	struct mwl8k_priv *priv = hw->priv;
	struct mwl8k_vif *mwl8k_vif = MWL8K_VIF(vif);
	struct mwl8k_cmd_update_mac_addr *cmd;
	int mac_type;
	int rc;

	mac_type = MWL8K_MAC_TYPE_PRIMARY_AP;
	if (vif != NULL && vif->type == NL80211_IFTYPE_STATION) {
		if (mwl8k_vif->macid + 1 == ffs(priv->sta_macids_supported))
			if (priv->ap_fw)
				mac_type = MWL8K_MAC_TYPE_SECONDARY_CLIENT;
			else
				mac_type = MWL8K_MAC_TYPE_PRIMARY_CLIENT;
		else
			mac_type = MWL8K_MAC_TYPE_SECONDARY_CLIENT;
	} else if (vif != NULL && vif->type == NL80211_IFTYPE_AP) {
		if (mwl8k_vif->macid + 1 == ffs(priv->ap_macids_supported))
			mac_type = MWL8K_MAC_TYPE_PRIMARY_AP;
		else
			mac_type = MWL8K_MAC_TYPE_SECONDARY_AP;
	}

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		return -ENOMEM;

	if (set)
		cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_MAC_ADDR);
	else
		cmd->header.code = cpu_to_le16(MWL8K_CMD_DEL_MAC_ADDR);

	cmd->header.length = cpu_to_le16(sizeof(*cmd));
	if (priv->ap_fw) {
		cmd->mbss.mac_type = cpu_to_le16(mac_type);
		memcpy(cmd->mbss.mac_addr, mac, ETH_ALEN);
	} else {
		memcpy(cmd->mac_addr, mac, ETH_ALEN);
	}

	rc = mwl8k_post_pervif_cmd(hw, vif, &cmd->header);
	kfree(cmd);

	return rc;
}