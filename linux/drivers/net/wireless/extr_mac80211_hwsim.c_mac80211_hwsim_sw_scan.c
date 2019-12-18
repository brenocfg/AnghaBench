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
struct mac80211_hwsim_data {int scanning; int /*<<< orphan*/  mutex; int /*<<< orphan*/  survey_data; int /*<<< orphan*/  scan_addr; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct mac80211_hwsim_data* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void mac80211_hwsim_sw_scan(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif,
				   const u8 *mac_addr)
{
	struct mac80211_hwsim_data *hwsim = hw->priv;

	mutex_lock(&hwsim->mutex);

	if (hwsim->scanning) {
		pr_debug("two hwsim sw_scans detected!\n");
		goto out;
	}

	pr_debug("hwsim sw_scan request, prepping stuff\n");

	memcpy(hwsim->scan_addr, mac_addr, ETH_ALEN);
	hwsim->scanning = true;
	memset(hwsim->survey_data, 0, sizeof(hwsim->survey_data));

out:
	mutex_unlock(&hwsim->mutex);
}