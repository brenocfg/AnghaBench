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
struct iwl_priv {int /*<<< orphan*/ * scan_request; int /*<<< orphan*/ * scan_vif; int /*<<< orphan*/  scan_type; int /*<<< orphan*/  hw; } ;
struct cfg80211_scan_info {int aborted; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_SCAN (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  IWL_SCAN_NORMAL ; 
 int /*<<< orphan*/  ieee80211_scan_completed (int /*<<< orphan*/ ,struct cfg80211_scan_info*) ; 

__attribute__((used)) static void iwl_complete_scan(struct iwl_priv *priv, bool aborted)
{
	struct cfg80211_scan_info info = {
		.aborted = aborted,
	};

	/* check if scan was requested from mac80211 */
	if (priv->scan_request) {
		IWL_DEBUG_SCAN(priv, "Complete scan in mac80211\n");
		ieee80211_scan_completed(priv->hw, &info);
	}

	priv->scan_type = IWL_SCAN_NORMAL;
	priv->scan_vif = NULL;
	priv->scan_request = NULL;
}