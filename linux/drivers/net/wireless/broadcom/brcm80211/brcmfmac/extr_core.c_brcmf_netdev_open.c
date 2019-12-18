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
typedef  int u32 ;
struct net_device {int /*<<< orphan*/  features; } ;
struct brcmf_pub {struct brcmf_bus* bus_if; } ;
struct brcmf_if {int /*<<< orphan*/  pend_8021x_cnt; int /*<<< orphan*/  bsscfgidx; struct brcmf_pub* drvr; } ;
struct brcmf_bus {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ BRCMF_BUS_UP ; 
 int EAGAIN ; 
 int EIO ; 
 int /*<<< orphan*/  NETIF_F_IP_CSUM ; 
 int TOE_TX_CSUM_OL ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*) ; 
 scalar_t__ brcmf_cfg80211_up (struct net_device*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ brcmf_fil_iovar_int_get (struct brcmf_if*,char*,int*) ; 
 struct brcmf_if* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 

__attribute__((used)) static int brcmf_netdev_open(struct net_device *ndev)
{
	struct brcmf_if *ifp = netdev_priv(ndev);
	struct brcmf_pub *drvr = ifp->drvr;
	struct brcmf_bus *bus_if = drvr->bus_if;
	u32 toe_ol;

	brcmf_dbg(TRACE, "Enter, bsscfgidx=%d\n", ifp->bsscfgidx);

	/* If bus is not ready, can't continue */
	if (bus_if->state != BRCMF_BUS_UP) {
		bphy_err(drvr, "failed bus is not ready\n");
		return -EAGAIN;
	}

	atomic_set(&ifp->pend_8021x_cnt, 0);

	/* Get current TOE mode from dongle */
	if (brcmf_fil_iovar_int_get(ifp, "toe_ol", &toe_ol) >= 0
	    && (toe_ol & TOE_TX_CSUM_OL) != 0)
		ndev->features |= NETIF_F_IP_CSUM;
	else
		ndev->features &= ~NETIF_F_IP_CSUM;

	if (brcmf_cfg80211_up(ndev)) {
		bphy_err(drvr, "failed to bring up cfg80211\n");
		return -EIO;
	}

	/* Clear, carrier, set when connected or AP mode. */
	netif_carrier_off(ndev);
	return 0;
}