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
struct net_device {int dummy; } ;
struct brcmf_if {struct brcmf_cfg80211_vif* vif; } ;
struct brcmf_cfg80211_vif {int dummy; } ;

/* Variables and functions */
 struct brcmf_if* netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline struct brcmf_cfg80211_vif *ndev_to_vif(struct net_device *ndev)
{
	struct brcmf_if *ifp = netdev_priv(ndev);
	return ifp->vif;
}