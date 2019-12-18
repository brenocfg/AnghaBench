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
struct ath6kl_vif {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int __ath6kl_cfg80211_sscan_stop (struct ath6kl_vif*) ; 
 struct ath6kl_vif* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ath6kl_cfg80211_sscan_stop(struct wiphy *wiphy,
				      struct net_device *dev, u64 reqid)
{
	struct ath6kl_vif *vif = netdev_priv(dev);
	bool stopped;

	stopped = __ath6kl_cfg80211_sscan_stop(vif);

	if (!stopped)
		return -EIO;

	return 0;
}