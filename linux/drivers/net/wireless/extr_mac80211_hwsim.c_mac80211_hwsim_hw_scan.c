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
struct mac80211_hwsim_data {int /*<<< orphan*/  hw_scan; int /*<<< orphan*/  hw; int /*<<< orphan*/  mutex; int /*<<< orphan*/  survey_data; int /*<<< orphan*/  scan_addr; scalar_t__ scan_chan_idx; struct ieee80211_vif* hw_scan_vif; struct cfg80211_scan_request* hw_scan_request; scalar_t__ tmp_chan; } ;
struct ieee80211_vif {int /*<<< orphan*/  addr; } ;
struct cfg80211_scan_request {int flags; int /*<<< orphan*/  mac_addr_mask; int /*<<< orphan*/  mac_addr; } ;
struct ieee80211_scan_request {struct cfg80211_scan_request req; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct mac80211_hwsim_data* priv; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int NL80211_SCAN_FLAG_RANDOM_ADDR ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  get_random_mask_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mac80211_hwsim_hw_scan(struct ieee80211_hw *hw,
				  struct ieee80211_vif *vif,
				  struct ieee80211_scan_request *hw_req)
{
	struct mac80211_hwsim_data *hwsim = hw->priv;
	struct cfg80211_scan_request *req = &hw_req->req;

	mutex_lock(&hwsim->mutex);
	if (WARN_ON(hwsim->tmp_chan || hwsim->hw_scan_request)) {
		mutex_unlock(&hwsim->mutex);
		return -EBUSY;
	}
	hwsim->hw_scan_request = req;
	hwsim->hw_scan_vif = vif;
	hwsim->scan_chan_idx = 0;
	if (req->flags & NL80211_SCAN_FLAG_RANDOM_ADDR)
		get_random_mask_addr(hwsim->scan_addr,
				     hw_req->req.mac_addr,
				     hw_req->req.mac_addr_mask);
	else
		memcpy(hwsim->scan_addr, vif->addr, ETH_ALEN);
	memset(hwsim->survey_data, 0, sizeof(hwsim->survey_data));
	mutex_unlock(&hwsim->mutex);

	wiphy_dbg(hw->wiphy, "hwsim hw_scan request\n");

	ieee80211_queue_delayed_work(hwsim->hw, &hwsim->hw_scan, 0);

	return 0;
}