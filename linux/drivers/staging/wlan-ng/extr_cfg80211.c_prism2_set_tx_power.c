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
typedef  int u32 ;
struct wlandevice {int dummy; } ;
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct prism2_wiphy_private {struct wlandevice* wlandev; } ;
typedef  enum nl80211_tx_power_setting { ____Placeholder_nl80211_tx_power_setting } nl80211_tx_power_setting ;

/* Variables and functions */
 int /*<<< orphan*/  DIDMIB_DOT11PHY_TXPOWERTABLE_CURRENTTXPOWERLEVEL ; 
 int EFAULT ; 
 int MBM_TO_DBM (int) ; 
 int NL80211_TX_POWER_AUTOMATIC ; 
 int prism2_domibset_uint32 (struct wlandevice*,int /*<<< orphan*/ ,int) ; 
 struct prism2_wiphy_private* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int prism2_set_tx_power(struct wiphy *wiphy, struct wireless_dev *wdev,
			       enum nl80211_tx_power_setting type, int mbm)
{
	struct prism2_wiphy_private *priv = wiphy_priv(wiphy);
	struct wlandevice *wlandev = priv->wlandev;
	u32 data;
	int result;
	int err = 0;

	if (type == NL80211_TX_POWER_AUTOMATIC)
		data = 30;
	else
		data = MBM_TO_DBM(mbm);

	result = prism2_domibset_uint32(wlandev,
		DIDMIB_DOT11PHY_TXPOWERTABLE_CURRENTTXPOWERLEVEL,
		data);

	if (result) {
		err = -EFAULT;
		goto exit;
	}

exit:
	return err;
}