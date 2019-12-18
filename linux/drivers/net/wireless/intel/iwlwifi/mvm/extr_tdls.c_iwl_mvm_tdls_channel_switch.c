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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct iwl_mvm_sta {scalar_t__ sta_id; } ;
struct cfg80211_chan_def {int /*<<< orphan*/  width; TYPE_1__* chan; } ;
struct TYPE_6__ {scalar_t__ sta_id; int /*<<< orphan*/  ch_sw_tm_ie; int /*<<< orphan*/  op_class; int /*<<< orphan*/  initiator; struct cfg80211_chan_def chandef; int /*<<< orphan*/  skb; } ;
struct TYPE_8__ {int /*<<< orphan*/  dwork; TYPE_2__ peer; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; TYPE_4__ tdls_cs; } ;
struct TYPE_7__ {int dtim_period; int beacon_int; } ;
struct ieee80211_vif {TYPE_3__ bss_conf; } ;
struct ieee80211_sta {int /*<<< orphan*/  tdls_initiator; int /*<<< orphan*/  addr; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IWL_DEBUG_TDLS (struct iwl_mvm*,char*,int /*<<< orphan*/ ,...) ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 scalar_t__ IWL_MVM_INVALID_STA ; 
 int /*<<< orphan*/  TDLS_SEND_CHAN_SW_REQ ; 
 int TU_TO_MS (int) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 int iwl_mvm_tdls_config_channel_switch (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cfg80211_chan_def*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_wq ; 

int
iwl_mvm_tdls_channel_switch(struct ieee80211_hw *hw,
			    struct ieee80211_vif *vif,
			    struct ieee80211_sta *sta, u8 oper_class,
			    struct cfg80211_chan_def *chandef,
			    struct sk_buff *tmpl_skb, u32 ch_sw_tm_ie)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	struct iwl_mvm_sta *mvmsta;
	unsigned int delay;
	int ret;

	mutex_lock(&mvm->mutex);

	IWL_DEBUG_TDLS(mvm, "TDLS channel switch with %pM ch %d width %d\n",
		       sta->addr, chandef->chan->center_freq, chandef->width);

	/* we only support a single peer for channel switching */
	if (mvm->tdls_cs.peer.sta_id != IWL_MVM_INVALID_STA) {
		IWL_DEBUG_TDLS(mvm,
			       "Existing peer. Can't start switch with %pM\n",
			       sta->addr);
		ret = -EBUSY;
		goto out;
	}

	ret = iwl_mvm_tdls_config_channel_switch(mvm, vif,
						 TDLS_SEND_CHAN_SW_REQ,
						 sta->addr, sta->tdls_initiator,
						 oper_class, chandef, 0, 0, 0,
						 tmpl_skb, ch_sw_tm_ie);
	if (ret)
		goto out;

	/*
	 * Mark the peer as "in tdls switch" for this vif. We only allow a
	 * single such peer per vif.
	 */
	mvm->tdls_cs.peer.skb = skb_copy(tmpl_skb, GFP_KERNEL);
	if (!mvm->tdls_cs.peer.skb) {
		ret = -ENOMEM;
		goto out;
	}

	mvmsta = iwl_mvm_sta_from_mac80211(sta);
	mvm->tdls_cs.peer.sta_id = mvmsta->sta_id;
	mvm->tdls_cs.peer.chandef = *chandef;
	mvm->tdls_cs.peer.initiator = sta->tdls_initiator;
	mvm->tdls_cs.peer.op_class = oper_class;
	mvm->tdls_cs.peer.ch_sw_tm_ie = ch_sw_tm_ie;

	/*
	 * Wait for 2 DTIM periods before attempting the next switch. The next
	 * switch will be made sooner if the current one completes before that.
	 */
	delay = 2 * TU_TO_MS(vif->bss_conf.dtim_period *
			     vif->bss_conf.beacon_int);
	mod_delayed_work(system_wq, &mvm->tdls_cs.dwork,
			 msecs_to_jiffies(delay));

out:
	mutex_unlock(&mvm->mutex);
	return ret;
}