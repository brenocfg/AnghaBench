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
struct wiphy {int dummy; } ;
struct regulatory_request {int /*<<< orphan*/  dfs_region; } ;
struct ieee80211_hw {struct ath10k* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  regulatory; } ;
struct ath10k {scalar_t__ state; int phy_capability; TYPE_3__* hw; int /*<<< orphan*/  conf_mutex; TYPE_4__* dfs_detector; TYPE_1__ ath_common; } ;
struct TYPE_8__ {int (* set_dfs_domain ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {TYPE_2__* wiphy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * bands; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_REGULATORY ; 
 scalar_t__ ATH10K_STATE_ON ; 
 int /*<<< orphan*/  CONFIG_ATH10K_DFS_CERTIFIED ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 size_t NL80211_BAND_5GHZ ; 
 int WHAL_WLAN_11A_CAPABILITY ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_mac_update_channel_list (struct ath10k*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_regd_update (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_reg_notifier_apply (struct wiphy*,struct regulatory_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 struct ieee80211_hw* wiphy_to_ieee80211_hw (struct wiphy*) ; 

__attribute__((used)) static void ath10k_reg_notifier(struct wiphy *wiphy,
				struct regulatory_request *request)
{
	struct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	struct ath10k *ar = hw->priv;
	bool result;

	ath_reg_notifier_apply(wiphy, request, &ar->ath_common.regulatory);

	if (IS_ENABLED(CONFIG_ATH10K_DFS_CERTIFIED) && ar->dfs_detector) {
		ath10k_dbg(ar, ATH10K_DBG_REGULATORY, "dfs region 0x%x\n",
			   request->dfs_region);
		result = ar->dfs_detector->set_dfs_domain(ar->dfs_detector,
							  request->dfs_region);
		if (!result)
			ath10k_warn(ar, "DFS region 0x%X not supported, will trigger radar for every pulse\n",
				    request->dfs_region);
	}

	mutex_lock(&ar->conf_mutex);
	if (ar->state == ATH10K_STATE_ON)
		ath10k_regd_update(ar);
	mutex_unlock(&ar->conf_mutex);

	if (ar->phy_capability & WHAL_WLAN_11A_CAPABILITY)
		ath10k_mac_update_channel_list(ar,
					       ar->hw->wiphy->bands[NL80211_BAND_5GHZ]);
}