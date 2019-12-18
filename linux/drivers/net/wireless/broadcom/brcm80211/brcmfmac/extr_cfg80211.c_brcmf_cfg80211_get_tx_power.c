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
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_cfg80211_vif {int /*<<< orphan*/  ifp; } ;
struct brcmf_cfg80211_info {struct brcmf_pub* pub; } ;
typedef  int s32 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  TRACE ; 
 int WL_TXPWR_OVERRIDE ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,int) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int brcmf_fil_iovar_int_get (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  check_vif_up (struct brcmf_cfg80211_vif*) ; 
 struct brcmf_cfg80211_vif* wdev_to_vif (struct wireless_dev*) ; 
 struct brcmf_cfg80211_info* wiphy_to_cfg (struct wiphy*) ; 

__attribute__((used)) static s32
brcmf_cfg80211_get_tx_power(struct wiphy *wiphy, struct wireless_dev *wdev,
			    s32 *dbm)
{
	struct brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	struct brcmf_cfg80211_vif *vif = wdev_to_vif(wdev);
	struct brcmf_pub *drvr = cfg->pub;
	s32 qdbm = 0;
	s32 err;

	brcmf_dbg(TRACE, "Enter\n");
	if (!check_vif_up(vif))
		return -EIO;

	err = brcmf_fil_iovar_int_get(vif->ifp, "qtxpower", &qdbm);
	if (err) {
		bphy_err(drvr, "error (%d)\n", err);
		goto done;
	}
	*dbm = (qdbm & ~WL_TXPWR_OVERRIDE) / 4;

done:
	brcmf_dbg(TRACE, "Exit (0x%x %d)\n", qdbm, *dbm);
	return err;
}