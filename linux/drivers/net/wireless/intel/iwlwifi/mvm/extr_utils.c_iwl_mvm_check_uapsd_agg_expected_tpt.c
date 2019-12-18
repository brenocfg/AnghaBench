#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_6__ {TYPE_2__* data; } ;
struct iwl_mvm {int /*<<< orphan*/ * vif_id_to_mac; TYPE_3__ tcm; } ;
struct ieee80211_vif {int dummy; } ;
struct TYPE_4__ {int rx_bytes; scalar_t__ detected; int /*<<< orphan*/  rate; } ;
struct TYPE_5__ {TYPE_1__ uapsd_nonagg_detect; scalar_t__ opened_rx_ba_sessions; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,unsigned int) ; 
 unsigned long ewma_rate_read (int /*<<< orphan*/ *) ; 
 scalar_t__ iwl_mvm_has_new_rx_api (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_uapsd_agg_disconnect (struct iwl_mvm*,struct ieee80211_vif*) ; 
 struct ieee80211_vif* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void iwl_mvm_check_uapsd_agg_expected_tpt(struct iwl_mvm *mvm,
						 unsigned int elapsed,
						 int mac)
{
	u64 bytes = mvm->tcm.data[mac].uapsd_nonagg_detect.rx_bytes;
	u64 tpt;
	unsigned long rate;
	struct ieee80211_vif *vif;

	rate = ewma_rate_read(&mvm->tcm.data[mac].uapsd_nonagg_detect.rate);

	if (!rate || mvm->tcm.data[mac].opened_rx_ba_sessions ||
	    mvm->tcm.data[mac].uapsd_nonagg_detect.detected)
		return;

	if (iwl_mvm_has_new_rx_api(mvm)) {
		tpt = 8 * bytes; /* kbps */
		do_div(tpt, elapsed);
		rate *= 1000; /* kbps */
		if (tpt < 22 * rate / 100)
			return;
	} else {
		/*
		 * the rate here is actually the threshold, in 100Kbps units,
		 * so do the needed conversion from bytes to 100Kbps:
		 * 100kb = bits / (100 * 1000),
		 * 100kbps = 100kb / (msecs / 1000) ==
		 *           (bits / (100 * 1000)) / (msecs / 1000) ==
		 *           bits / (100 * msecs)
		 */
		tpt = (8 * bytes);
		do_div(tpt, elapsed * 100);
		if (tpt < rate)
			return;
	}

	rcu_read_lock();
	vif = rcu_dereference(mvm->vif_id_to_mac[mac]);
	if (vif)
		iwl_mvm_uapsd_agg_disconnect(mvm, vif);
	rcu_read_unlock();
}