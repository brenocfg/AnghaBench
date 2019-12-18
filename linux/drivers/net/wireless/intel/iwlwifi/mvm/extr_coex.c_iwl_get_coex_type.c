#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_10__ {int /*<<< orphan*/  secondary_ch_lut; int /*<<< orphan*/  primary_ch_lut; } ;
struct TYPE_9__ {int /*<<< orphan*/  secondary_ch_phy_id; int /*<<< orphan*/  primary_ch_phy_id; } ;
struct iwl_mvm {TYPE_5__ last_bt_notif; TYPE_4__ last_bt_ci_cmd; TYPE_3__* cfg; } ;
struct ieee80211_vif {int /*<<< orphan*/  chanctx_conf; } ;
struct TYPE_7__ {TYPE_1__* chan; } ;
struct ieee80211_chanctx_conf {scalar_t__ drv_priv; TYPE_2__ def; } ;
typedef  enum iwl_bt_coex_lut_type { ____Placeholder_iwl_bt_coex_lut_type } iwl_bt_coex_lut_type ;
struct TYPE_8__ {scalar_t__ bt_shared_single_ant; } ;
struct TYPE_6__ {scalar_t__ band; } ;

/* Variables and functions */
 int BT_COEX_INVALID_LUT ; 
 int BT_COEX_TX_DIS_LUT ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct ieee80211_chanctx_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static enum iwl_bt_coex_lut_type
iwl_get_coex_type(struct iwl_mvm *mvm, const struct ieee80211_vif *vif)
{
	struct ieee80211_chanctx_conf *chanctx_conf;
	enum iwl_bt_coex_lut_type ret;
	u16 phy_ctx_id;
	u32 primary_ch_phy_id, secondary_ch_phy_id;

	/*
	 * Checking that we hold mvm->mutex is a good idea, but the rate
	 * control can't acquire the mutex since it runs in Tx path.
	 * So this is racy in that case, but in the worst case, the AMPDU
	 * size limit will be wrong for a short time which is not a big
	 * issue.
	 */

	rcu_read_lock();

	chanctx_conf = rcu_dereference(vif->chanctx_conf);

	if (!chanctx_conf ||
	     chanctx_conf->def.chan->band != NL80211_BAND_2GHZ) {
		rcu_read_unlock();
		return BT_COEX_INVALID_LUT;
	}

	ret = BT_COEX_TX_DIS_LUT;

	if (mvm->cfg->bt_shared_single_ant) {
		rcu_read_unlock();
		return ret;
	}

	phy_ctx_id = *((u16 *)chanctx_conf->drv_priv);
	primary_ch_phy_id = le32_to_cpu(mvm->last_bt_ci_cmd.primary_ch_phy_id);
	secondary_ch_phy_id =
		le32_to_cpu(mvm->last_bt_ci_cmd.secondary_ch_phy_id);

	if (primary_ch_phy_id == phy_ctx_id)
		ret = le32_to_cpu(mvm->last_bt_notif.primary_ch_lut);
	else if (secondary_ch_phy_id == phy_ctx_id)
		ret = le32_to_cpu(mvm->last_bt_notif.secondary_ch_lut);
	/* else - default = TX TX disallowed */

	rcu_read_unlock();

	return ret;
}