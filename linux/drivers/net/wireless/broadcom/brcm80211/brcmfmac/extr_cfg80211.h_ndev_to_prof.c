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
struct net_device {int dummy; } ;
struct brcmf_if {TYPE_1__* vif; } ;
struct brcmf_cfg80211_profile {int dummy; } ;
struct TYPE_2__ {struct brcmf_cfg80211_profile profile; } ;

/* Variables and functions */
 struct brcmf_if* netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline struct brcmf_cfg80211_profile *ndev_to_prof(struct net_device *nd)
{
	struct brcmf_if *ifp = netdev_priv(nd);
	return &ifp->vif->profile;
}