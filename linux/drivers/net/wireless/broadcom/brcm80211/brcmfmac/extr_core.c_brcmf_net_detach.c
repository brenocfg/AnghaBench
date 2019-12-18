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
struct net_device {scalar_t__ reg_state; } ;

/* Variables and functions */
 scalar_t__ NETREG_REGISTERED ; 
 int /*<<< orphan*/  brcmf_cfg80211_free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 

__attribute__((used)) static void brcmf_net_detach(struct net_device *ndev, bool rtnl_locked)
{
	if (ndev->reg_state == NETREG_REGISTERED) {
		if (rtnl_locked)
			unregister_netdevice(ndev);
		else
			unregister_netdev(ndev);
	} else {
		brcmf_cfg80211_free_netdev(ndev);
		free_netdev(ndev);
	}
}