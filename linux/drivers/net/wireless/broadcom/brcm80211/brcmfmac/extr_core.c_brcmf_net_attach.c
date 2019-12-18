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
struct net_device {int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  name; int /*<<< orphan*/  priv_destructor; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/  needed_headroom; } ;
struct brcmf_pub {int /*<<< orphan*/ ** iflist; int /*<<< orphan*/  config; scalar_t__ hdrlen; } ;
struct brcmf_if {size_t bsscfgidx; int /*<<< orphan*/  ndoffload_work; int /*<<< orphan*/  multicast_work; int /*<<< orphan*/  mac_addr; struct net_device* ndev; struct brcmf_pub* drvr; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int EBADE ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  _brcmf_set_multicast_list ; 
 int /*<<< orphan*/  _brcmf_update_ndtable ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*) ; 
 int /*<<< orphan*/  brcmf_cfg80211_free_netdev ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/  brcmf_ethtool_ops ; 
 int /*<<< orphan*/  brcmf_netdev_ops_pri ; 
 int /*<<< orphan*/  cfg_to_wiphy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net_set (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ register_netdev (struct net_device*) ; 
 scalar_t__ register_netdevice (struct net_device*) ; 
 int /*<<< orphan*/  wiphy_net (int /*<<< orphan*/ ) ; 

int brcmf_net_attach(struct brcmf_if *ifp, bool rtnl_locked)
{
	struct brcmf_pub *drvr = ifp->drvr;
	struct net_device *ndev;
	s32 err;

	brcmf_dbg(TRACE, "Enter, bsscfgidx=%d mac=%pM\n", ifp->bsscfgidx,
		  ifp->mac_addr);
	ndev = ifp->ndev;

	/* set appropriate operations */
	ndev->netdev_ops = &brcmf_netdev_ops_pri;

	ndev->needed_headroom += drvr->hdrlen;
	ndev->ethtool_ops = &brcmf_ethtool_ops;

	/* set the mac address & netns */
	memcpy(ndev->dev_addr, ifp->mac_addr, ETH_ALEN);
	dev_net_set(ndev, wiphy_net(cfg_to_wiphy(drvr->config)));

	INIT_WORK(&ifp->multicast_work, _brcmf_set_multicast_list);
	INIT_WORK(&ifp->ndoffload_work, _brcmf_update_ndtable);

	if (rtnl_locked)
		err = register_netdevice(ndev);
	else
		err = register_netdev(ndev);
	if (err != 0) {
		bphy_err(drvr, "couldn't register the net device\n");
		goto fail;
	}

	ndev->priv_destructor = brcmf_cfg80211_free_netdev;
	brcmf_dbg(INFO, "%s: Broadcom Dongle Host Driver\n", ndev->name);
	return 0;

fail:
	drvr->iflist[ifp->bsscfgidx] = NULL;
	ndev->netdev_ops = NULL;
	return -EBADE;
}