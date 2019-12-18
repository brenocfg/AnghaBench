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
struct net_device {int /*<<< orphan*/  ieee80211_ptr; } ;
struct brcmf_cfg80211_info {int dummy; } ;

/* Variables and functions */
 struct brcmf_cfg80211_info* wdev_to_cfg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct brcmf_cfg80211_info *ndev_to_cfg(struct net_device *ndev)
{
	return wdev_to_cfg(ndev->ieee80211_ptr);
}