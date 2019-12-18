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
struct brcmf_cfg80211_info {int /*<<< orphan*/  pub; } ;
struct TYPE_2__ {struct net_device* ndev; } ;

/* Variables and functions */
 TYPE_1__* brcmf_get_ifp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
struct net_device *cfg_to_ndev(struct brcmf_cfg80211_info *cfg)
{
	return brcmf_get_ifp(cfg->pub, 0)->ndev;
}