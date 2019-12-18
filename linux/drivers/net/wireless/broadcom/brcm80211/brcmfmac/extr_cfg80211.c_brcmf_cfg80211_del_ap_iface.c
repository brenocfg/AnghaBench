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
struct wireless_dev {struct net_device* netdev; } ;
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_if {int /*<<< orphan*/ * vif; } ;
struct brcmf_cfg80211_info {struct brcmf_pub* pub; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_E_IF_DEL ; 
 int /*<<< orphan*/  BRCMF_VIF_EVENT_TIMEOUT ; 
 int EIO ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,...) ; 
 int /*<<< orphan*/  brcmf_cfg80211_arm_vif_event (struct brcmf_cfg80211_info*,int /*<<< orphan*/ *) ; 
 int brcmf_cfg80211_wait_vif_event (struct brcmf_cfg80211_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int brcmf_fil_bsscfg_data_set (struct brcmf_if*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_remove_interface (struct brcmf_if*,int) ; 
 struct brcmf_if* netdev_priv (struct net_device*) ; 
 struct brcmf_cfg80211_info* wiphy_to_cfg (struct wiphy*) ; 

__attribute__((used)) static int brcmf_cfg80211_del_ap_iface(struct wiphy *wiphy,
				       struct wireless_dev *wdev)
{
	struct brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	struct net_device *ndev = wdev->netdev;
	struct brcmf_if *ifp = netdev_priv(ndev);
	struct brcmf_pub *drvr = cfg->pub;
	int ret;
	int err;

	brcmf_cfg80211_arm_vif_event(cfg, ifp->vif);

	err = brcmf_fil_bsscfg_data_set(ifp, "interface_remove", NULL, 0);
	if (err) {
		bphy_err(drvr, "interface_remove failed %d\n", err);
		goto err_unarm;
	}

	/* wait for firmware event */
	ret = brcmf_cfg80211_wait_vif_event(cfg, BRCMF_E_IF_DEL,
					    BRCMF_VIF_EVENT_TIMEOUT);
	if (!ret) {
		bphy_err(drvr, "timeout occurred\n");
		err = -EIO;
		goto err_unarm;
	}

	brcmf_remove_interface(ifp, true);

err_unarm:
	brcmf_cfg80211_arm_vif_event(cfg, NULL);
	return err;
}