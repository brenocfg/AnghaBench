#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct brcmf_if {int /*<<< orphan*/  ndev; } ;
struct TYPE_2__ {int active; int nd_enabled; int /*<<< orphan*/  pre_pmmode; } ;
struct brcmf_cfg80211_info {TYPE_1__ wowl; int /*<<< orphan*/  pub; int /*<<< orphan*/  wiphy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_C_SET_PM ; 
 int /*<<< orphan*/  BRCMF_E_PFN_NET_FOUND ; 
 int /*<<< orphan*/  BRCMF_FEAT_WOWL_ARP_ND ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_cfg80211_sched_scan_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_config_wowl_pattern (struct brcmf_if*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_configure_arp_nd_offload (struct brcmf_if*,int) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_feat_is_enabled (struct brcmf_if*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_fil_cmd_int_set (struct brcmf_if*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_fil_iovar_int_set (struct brcmf_if*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_fweh_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_fweh_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_notify_sched_scan_results ; 
 int /*<<< orphan*/  brcmf_report_wowl_wakeind (struct wiphy*,struct brcmf_if*) ; 
 struct net_device* cfg_to_ndev (struct brcmf_cfg80211_info*) ; 
 struct brcmf_if* netdev_priv (struct net_device*) ; 
 struct brcmf_cfg80211_info* wiphy_to_cfg (struct wiphy*) ; 

__attribute__((used)) static s32 brcmf_cfg80211_resume(struct wiphy *wiphy)
{
	struct brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	struct net_device *ndev = cfg_to_ndev(cfg);
	struct brcmf_if *ifp = netdev_priv(ndev);

	brcmf_dbg(TRACE, "Enter\n");

	if (cfg->wowl.active) {
		brcmf_report_wowl_wakeind(wiphy, ifp);
		brcmf_fil_iovar_int_set(ifp, "wowl_clear", 0);
		brcmf_config_wowl_pattern(ifp, "clr", NULL, 0, NULL, 0);
		if (!brcmf_feat_is_enabled(ifp, BRCMF_FEAT_WOWL_ARP_ND))
			brcmf_configure_arp_nd_offload(ifp, true);
		brcmf_fil_cmd_int_set(ifp, BRCMF_C_SET_PM,
				      cfg->wowl.pre_pmmode);
		cfg->wowl.active = false;
		if (cfg->wowl.nd_enabled) {
			brcmf_cfg80211_sched_scan_stop(cfg->wiphy, ifp->ndev, 0);
			brcmf_fweh_unregister(cfg->pub, BRCMF_E_PFN_NET_FOUND);
			brcmf_fweh_register(cfg->pub, BRCMF_E_PFN_NET_FOUND,
					    brcmf_notify_sched_scan_results);
			cfg->wowl.nd_enabled = false;
		}
	}
	return 0;
}