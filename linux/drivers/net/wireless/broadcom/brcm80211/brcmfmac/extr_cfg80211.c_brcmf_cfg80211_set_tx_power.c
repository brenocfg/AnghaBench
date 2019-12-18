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
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_if {int /*<<< orphan*/  vif; } ;
struct brcmf_cfg80211_info {struct brcmf_pub* pub; } ;
typedef  int s32 ;
typedef  enum nl80211_tx_power_setting { ____Placeholder_nl80211_tx_power_setting } nl80211_tx_power_setting ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_C_SET_RADIO ; 
 int EINVAL ; 
 int EIO ; 
 int MBM_TO_DBM (int) ; 
#define  NL80211_TX_POWER_AUTOMATIC 130 
#define  NL80211_TX_POWER_FIXED 129 
#define  NL80211_TX_POWER_LIMITED 128 
 int /*<<< orphan*/  TRACE ; 
 int WL_RADIO_SW_DISABLE ; 
 int WL_TXPWR_OVERRIDE ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,...) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int brcmf_fil_cmd_int_set (struct brcmf_if*,int /*<<< orphan*/ ,int) ; 
 int brcmf_fil_iovar_int_set (struct brcmf_if*,char*,int) ; 
 struct net_device* cfg_to_ndev (struct brcmf_cfg80211_info*) ; 
 int /*<<< orphan*/  check_vif_up (int /*<<< orphan*/ ) ; 
 struct brcmf_if* netdev_priv (struct net_device*) ; 
 struct brcmf_cfg80211_info* wiphy_to_cfg (struct wiphy*) ; 

__attribute__((used)) static s32
brcmf_cfg80211_set_tx_power(struct wiphy *wiphy, struct wireless_dev *wdev,
			    enum nl80211_tx_power_setting type, s32 mbm)
{
	struct brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	struct net_device *ndev = cfg_to_ndev(cfg);
	struct brcmf_if *ifp = netdev_priv(ndev);
	struct brcmf_pub *drvr = cfg->pub;
	s32 err;
	s32 disable;
	u32 qdbm = 127;

	brcmf_dbg(TRACE, "Enter %d %d\n", type, mbm);
	if (!check_vif_up(ifp->vif))
		return -EIO;

	switch (type) {
	case NL80211_TX_POWER_AUTOMATIC:
		break;
	case NL80211_TX_POWER_LIMITED:
	case NL80211_TX_POWER_FIXED:
		if (mbm < 0) {
			bphy_err(drvr, "TX_POWER_FIXED - dbm is negative\n");
			err = -EINVAL;
			goto done;
		}
		qdbm =  MBM_TO_DBM(4 * mbm);
		if (qdbm > 127)
			qdbm = 127;
		qdbm |= WL_TXPWR_OVERRIDE;
		break;
	default:
		bphy_err(drvr, "Unsupported type %d\n", type);
		err = -EINVAL;
		goto done;
	}
	/* Make sure radio is off or on as far as software is concerned */
	disable = WL_RADIO_SW_DISABLE << 16;
	err = brcmf_fil_cmd_int_set(ifp, BRCMF_C_SET_RADIO, disable);
	if (err)
		bphy_err(drvr, "WLC_SET_RADIO error (%d)\n", err);

	err = brcmf_fil_iovar_int_set(ifp, "qtxpower", qdbm);
	if (err)
		bphy_err(drvr, "qtxpower error (%d)\n", err);

done:
	brcmf_dbg(TRACE, "Exit %d (qdbm)\n", qdbm & ~WL_TXPWR_OVERRIDE);
	return err;
}