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
typedef  int /*<<< orphan*/  u64 ;
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct brcmf_if {int dummy; } ;
struct brcmf_cfg80211_info {scalar_t__ int_escan_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCAN ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_notify_escan_complete (struct brcmf_cfg80211_info*,struct brcmf_if*,int,int) ; 
 int /*<<< orphan*/  brcmf_pno_stop_sched_scan (struct brcmf_if*,int /*<<< orphan*/ ) ; 
 struct brcmf_if* netdev_priv (struct net_device*) ; 
 struct brcmf_cfg80211_info* wiphy_to_cfg (struct wiphy*) ; 

__attribute__((used)) static int brcmf_cfg80211_sched_scan_stop(struct wiphy *wiphy,
					  struct net_device *ndev, u64 reqid)
{
	struct brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	struct brcmf_if *ifp = netdev_priv(ndev);

	brcmf_dbg(SCAN, "enter\n");
	brcmf_pno_stop_sched_scan(ifp, reqid);
	if (cfg->int_escan_map)
		brcmf_notify_escan_complete(cfg, ifp, true, true);
	return 0;
}