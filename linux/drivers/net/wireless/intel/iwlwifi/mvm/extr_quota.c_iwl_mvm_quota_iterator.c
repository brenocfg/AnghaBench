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
typedef  scalar_t__ u16 ;
struct iwl_mvm_vif {scalar_t__ dbgfs_quota_min; TYPE_2__* phy_ctxt; int /*<<< orphan*/  monitor_active; int /*<<< orphan*/  ap_ibss_active; } ;
struct iwl_mvm_quota_iterator_data {scalar_t__* colors; int* low_latency; int /*<<< orphan*/  n_low_latency_bindings; int /*<<< orphan*/ * dbgfs_min; int /*<<< orphan*/ * n_interfaces; struct ieee80211_vif* disabled_vif; } ;
struct TYPE_3__ {int /*<<< orphan*/  assoc; } ;
struct ieee80211_vif {int type; TYPE_1__ bss_conf; } ;
struct TYPE_4__ {scalar_t__ id; scalar_t__ color; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ MAX_BINDINGS ; 
#define  NL80211_IFTYPE_ADHOC 132 
#define  NL80211_IFTYPE_AP 131 
#define  NL80211_IFTYPE_MONITOR 130 
#define  NL80211_IFTYPE_P2P_DEVICE 129 
#define  NL80211_IFTYPE_STATION 128 
 scalar_t__ NUM_PHY_CTX ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 scalar_t__ iwl_mvm_vif_low_latency (struct iwl_mvm_vif*) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void iwl_mvm_quota_iterator(void *_data, u8 *mac,
				   struct ieee80211_vif *vif)
{
	struct iwl_mvm_quota_iterator_data *data = _data;
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	u16 id;

	/* skip disabled interfaces here immediately */
	if (vif == data->disabled_vif)
		return;

	if (!mvmvif->phy_ctxt)
		return;

	/* currently, PHY ID == binding ID */
	id = mvmvif->phy_ctxt->id;

	/* need at least one binding per PHY */
	BUILD_BUG_ON(NUM_PHY_CTX > MAX_BINDINGS);

	if (WARN_ON_ONCE(id >= MAX_BINDINGS))
		return;

	switch (vif->type) {
	case NL80211_IFTYPE_STATION:
		if (vif->bss_conf.assoc)
			break;
		return;
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_ADHOC:
		if (mvmvif->ap_ibss_active)
			break;
		return;
	case NL80211_IFTYPE_MONITOR:
		if (mvmvif->monitor_active)
			break;
		return;
	case NL80211_IFTYPE_P2P_DEVICE:
		return;
	default:
		WARN_ON_ONCE(1);
		return;
	}

	if (data->colors[id] < 0)
		data->colors[id] = mvmvif->phy_ctxt->color;
	else
		WARN_ON_ONCE(data->colors[id] != mvmvif->phy_ctxt->color);

	data->n_interfaces[id]++;

#ifdef CONFIG_IWLWIFI_DEBUGFS
	if (mvmvif->dbgfs_quota_min)
		data->dbgfs_min[id] = max(data->dbgfs_min[id],
					  mvmvif->dbgfs_quota_min);
#endif

	if (iwl_mvm_vif_low_latency(mvmvif) && !data->low_latency[id]) {
		data->n_low_latency_bindings++;
		data->low_latency[id] = true;
	}
}