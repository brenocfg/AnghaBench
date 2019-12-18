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
struct wireless_dev {int iftype; } ;
struct wil6210_priv {int dummy; } ;
typedef  enum wmi_key_usage { ____Placeholder_wmi_key_usage } wmi_key_usage ;

/* Variables and functions */
#define  NL80211_IFTYPE_AP 131 
#define  NL80211_IFTYPE_P2P_CLIENT 130 
#define  NL80211_IFTYPE_P2P_GO 129 
#define  NL80211_IFTYPE_STATION 128 
 int WMI_KEY_USE_PAIRWISE ; 
 int WMI_KEY_USE_RX_GROUP ; 
 int WMI_KEY_USE_TX_GROUP ; 
 int /*<<< orphan*/ * key_usage_str ; 
 struct wil6210_priv* wdev_to_wil (struct wireless_dev*) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*) ; 

__attribute__((used)) static enum wmi_key_usage wil_detect_key_usage(struct wireless_dev *wdev,
					       bool pairwise)
{
	struct wil6210_priv *wil = wdev_to_wil(wdev);
	enum wmi_key_usage rc;

	if (pairwise) {
		rc = WMI_KEY_USE_PAIRWISE;
	} else {
		switch (wdev->iftype) {
		case NL80211_IFTYPE_STATION:
		case NL80211_IFTYPE_P2P_CLIENT:
			rc = WMI_KEY_USE_RX_GROUP;
			break;
		case NL80211_IFTYPE_AP:
		case NL80211_IFTYPE_P2P_GO:
			rc = WMI_KEY_USE_TX_GROUP;
			break;
		default:
			/* TODO: Rx GTK or Tx GTK? */
			wil_err(wil, "Can't determine GTK type\n");
			rc = WMI_KEY_USE_RX_GROUP;
			break;
		}
	}
	wil_dbg_misc(wil, "detect_key_usage: -> %s\n", key_usage_str[rc]);

	return rc;
}