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
struct net_device {int dummy; } ;
struct brcmf_if {int /*<<< orphan*/  vif; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_link_down (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_net_setcarrier (struct brcmf_if*,int) ; 
 int /*<<< orphan*/  check_vif_up (int /*<<< orphan*/ ) ; 
 struct brcmf_if* netdev_priv (struct net_device*) ; 

__attribute__((used)) static s32
brcmf_cfg80211_leave_ibss(struct wiphy *wiphy, struct net_device *ndev)
{
	struct brcmf_if *ifp = netdev_priv(ndev);

	brcmf_dbg(TRACE, "Enter\n");
	if (!check_vif_up(ifp->vif)) {
		/* When driver is being unloaded, it can end up here. If an
		 * error is returned then later on a debug trace in the wireless
		 * core module will be printed. To avoid this 0 is returned.
		 */
		return 0;
	}

	brcmf_link_down(ifp->vif, WLAN_REASON_DEAUTH_LEAVING);
	brcmf_net_setcarrier(ifp, false);

	brcmf_dbg(TRACE, "Exit\n");

	return 0;
}