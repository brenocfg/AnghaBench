#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct peer_capability_info {int extended_ht_caps; int interop; int station_id; scalar_t__ amsdu_enabled; int /*<<< orphan*/  ht_rates; int /*<<< orphan*/  legacy_rates; void* ht_caps; int /*<<< orphan*/  ht_support; void* basic_caps; int /*<<< orphan*/  peer_type; } ;
struct TYPE_14__ {void* length; void* code; } ;
struct mwl8k_cmd_update_stadb {TYPE_7__ header; struct peer_capability_info peer_info; int /*<<< orphan*/  peer_addr; int /*<<< orphan*/  action; } ;
struct TYPE_8__ {int assoc_capability; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;
struct TYPE_12__ {int /*<<< orphan*/  rx_mask; } ;
struct TYPE_13__ {int cap; int ampdu_factor; int ampdu_density; TYPE_5__ mcs; int /*<<< orphan*/  ht_supported; } ;
struct ieee80211_sta {int* supp_rates; TYPE_6__ ht_cap; int /*<<< orphan*/  addr; } ;
struct TYPE_10__ {TYPE_2__* chan; } ;
struct TYPE_11__ {TYPE_3__ chandef; } ;
struct ieee80211_hw {TYPE_4__ conf; } ;
struct TYPE_9__ {size_t band; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MWL8K_CMD_UPDATE_STADB ; 
 int /*<<< orphan*/  MWL8K_PEER_TYPE_ACCESSPOINT ; 
 int /*<<< orphan*/  MWL8K_STA_DB_MODIFY_ENTRY ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mwl8k_cmd_update_stadb*) ; 
 struct mwl8k_cmd_update_stadb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  legacy_rate_mask_to_array (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mwl8k_post_cmd (struct ieee80211_hw*,TYPE_7__*) ; 

__attribute__((used)) static int mwl8k_cmd_update_stadb_add(struct ieee80211_hw *hw,
				      struct ieee80211_vif *vif,
				      struct ieee80211_sta *sta)
{
	struct mwl8k_cmd_update_stadb *cmd;
	struct peer_capability_info *p;
	u32 rates;
	int rc;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		return -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_UPDATE_STADB);
	cmd->header.length = cpu_to_le16(sizeof(*cmd));
	cmd->action = cpu_to_le32(MWL8K_STA_DB_MODIFY_ENTRY);
	memcpy(cmd->peer_addr, sta->addr, ETH_ALEN);

	p = &cmd->peer_info;
	p->peer_type = MWL8K_PEER_TYPE_ACCESSPOINT;
	p->basic_caps = cpu_to_le16(vif->bss_conf.assoc_capability);
	p->ht_support = sta->ht_cap.ht_supported;
	p->ht_caps = cpu_to_le16(sta->ht_cap.cap);
	p->extended_ht_caps = (sta->ht_cap.ampdu_factor & 3) |
		((sta->ht_cap.ampdu_density & 7) << 2);
	if (hw->conf.chandef.chan->band == NL80211_BAND_2GHZ)
		rates = sta->supp_rates[NL80211_BAND_2GHZ];
	else
		rates = sta->supp_rates[NL80211_BAND_5GHZ] << 5;
	legacy_rate_mask_to_array(p->legacy_rates, rates);
	memcpy(p->ht_rates, sta->ht_cap.mcs.rx_mask, 16);
	p->interop = 1;
	p->amsdu_enabled = 0;

	rc = mwl8k_post_cmd(hw, &cmd->header);
	if (!rc)
		rc = p->station_id;
	kfree(cmd);

	return rc;
}