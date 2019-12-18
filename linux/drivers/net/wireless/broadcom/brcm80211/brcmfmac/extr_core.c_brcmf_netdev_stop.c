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
struct net_device {int dummy; } ;
struct brcmf_if {TYPE_2__* drvr; int /*<<< orphan*/  bsscfgidx; } ;
struct TYPE_4__ {TYPE_1__* bus_if; } ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ BRCMF_BUS_UP ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_cfg80211_down (struct net_device*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_fil_iovar_data_set (struct brcmf_if*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_net_setcarrier (struct brcmf_if*,int) ; 
 struct brcmf_if* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int brcmf_netdev_stop(struct net_device *ndev)
{
	struct brcmf_if *ifp = netdev_priv(ndev);

	brcmf_dbg(TRACE, "Enter, bsscfgidx=%d\n", ifp->bsscfgidx);

	brcmf_cfg80211_down(ndev);

	if (ifp->drvr->bus_if->state == BRCMF_BUS_UP)
		brcmf_fil_iovar_data_set(ifp, "arp_hostip_clear", NULL, 0);

	brcmf_net_setcarrier(ifp, false);

	return 0;
}