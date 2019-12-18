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
struct wiphy {int dummy; } ;
struct virt_wifi_wiphy_priv {int /*<<< orphan*/ * scan_request; int /*<<< orphan*/  scan_result; } ;
struct cfg80211_scan_info {int aborted; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfg80211_scan_done (int /*<<< orphan*/ *,struct cfg80211_scan_info*) ; 
 struct virt_wifi_wiphy_priv* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static void virt_wifi_cancel_scan(struct wiphy *wiphy)
{
	struct virt_wifi_wiphy_priv *priv = wiphy_priv(wiphy);

	cancel_delayed_work_sync(&priv->scan_result);
	/* Clean up dangling callbacks if necessary. */
	if (priv->scan_request) {
		struct cfg80211_scan_info scan_info = { .aborted = true };
		/* Schedules work which acquires and releases the rtnl lock. */
		cfg80211_scan_done(priv->scan_request, &scan_info);
		priv->scan_request = NULL;
	}
}