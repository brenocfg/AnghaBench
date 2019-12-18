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
struct wiphy {int max_scan_ssids; int max_scan_ie_len; int /*<<< orphan*/  interface_modes; int /*<<< orphan*/ ** bands; int /*<<< orphan*/  signal_type; } ;
struct virt_wifi_wiphy_priv {int being_deleted; int /*<<< orphan*/  scan_result; int /*<<< orphan*/ * scan_request; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFG80211_SIGNAL_TYPE_MBM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 size_t NL80211_BAND_60GHZ ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  band_2ghz ; 
 int /*<<< orphan*/  band_5ghz ; 
 int /*<<< orphan*/  virt_wifi_cfg80211_ops ; 
 int /*<<< orphan*/  virt_wifi_scan_result ; 
 int /*<<< orphan*/  wiphy_free (struct wiphy*) ; 
 struct wiphy* wiphy_new (int /*<<< orphan*/ *,int) ; 
 struct virt_wifi_wiphy_priv* wiphy_priv (struct wiphy*) ; 
 int wiphy_register (struct wiphy*) ; 

__attribute__((used)) static struct wiphy *virt_wifi_make_wiphy(void)
{
	struct wiphy *wiphy;
	struct virt_wifi_wiphy_priv *priv;
	int err;

	wiphy = wiphy_new(&virt_wifi_cfg80211_ops, sizeof(*priv));

	if (!wiphy)
		return NULL;

	wiphy->max_scan_ssids = 4;
	wiphy->max_scan_ie_len = 1000;
	wiphy->signal_type = CFG80211_SIGNAL_TYPE_MBM;

	wiphy->bands[NL80211_BAND_2GHZ] = &band_2ghz;
	wiphy->bands[NL80211_BAND_5GHZ] = &band_5ghz;
	wiphy->bands[NL80211_BAND_60GHZ] = NULL;

	wiphy->interface_modes = BIT(NL80211_IFTYPE_STATION);

	priv = wiphy_priv(wiphy);
	priv->being_deleted = false;
	priv->scan_request = NULL;
	INIT_DELAYED_WORK(&priv->scan_result, virt_wifi_scan_result);

	err = wiphy_register(wiphy);
	if (err < 0) {
		wiphy_free(wiphy);
		return NULL;
	}

	return wiphy;
}