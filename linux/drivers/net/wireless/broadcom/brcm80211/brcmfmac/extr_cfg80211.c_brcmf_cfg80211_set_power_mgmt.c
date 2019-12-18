#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_if {TYPE_2__* vif; } ;
struct brcmf_cfg80211_info {int pwr_save; struct brcmf_pub* pub; } ;
typedef  int s32 ;
struct TYPE_3__ {scalar_t__ iftype; } ;
struct TYPE_4__ {TYPE_1__ wdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_C_SET_PM ; 
 int ENODEV ; 
 int /*<<< orphan*/  INFO ; 
 scalar_t__ NL80211_IFTYPE_P2P_CLIENT ; 
 int PM_FAST ; 
 int PM_OFF ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,...) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int brcmf_fil_cmd_int_set (struct brcmf_if*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  check_vif_up (TYPE_2__*) ; 
 struct brcmf_if* netdev_priv (struct net_device*) ; 
 struct brcmf_cfg80211_info* wiphy_to_cfg (struct wiphy*) ; 

__attribute__((used)) static s32
brcmf_cfg80211_set_power_mgmt(struct wiphy *wiphy, struct net_device *ndev,
			   bool enabled, s32 timeout)
{
	s32 pm;
	s32 err = 0;
	struct brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	struct brcmf_if *ifp = netdev_priv(ndev);
	struct brcmf_pub *drvr = cfg->pub;

	brcmf_dbg(TRACE, "Enter\n");

	/*
	 * Powersave enable/disable request is coming from the
	 * cfg80211 even before the interface is up. In that
	 * scenario, driver will be storing the power save
	 * preference in cfg struct to apply this to
	 * FW later while initializing the dongle
	 */
	cfg->pwr_save = enabled;
	if (!check_vif_up(ifp->vif)) {

		brcmf_dbg(INFO, "Device is not ready, storing the value in cfg_info struct\n");
		goto done;
	}

	pm = enabled ? PM_FAST : PM_OFF;
	/* Do not enable the power save after assoc if it is a p2p interface */
	if (ifp->vif->wdev.iftype == NL80211_IFTYPE_P2P_CLIENT) {
		brcmf_dbg(INFO, "Do not enable power save for P2P clients\n");
		pm = PM_OFF;
	}
	brcmf_dbg(INFO, "power save %s\n", (pm ? "enabled" : "disabled"));

	err = brcmf_fil_cmd_int_set(ifp, BRCMF_C_SET_PM, pm);
	if (err) {
		if (err == -ENODEV)
			bphy_err(drvr, "net_device is not ready yet\n");
		else
			bphy_err(drvr, "error (%d)\n", err);
	}
done:
	brcmf_dbg(TRACE, "Exit\n");
	return err;
}