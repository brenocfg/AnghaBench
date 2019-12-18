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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int dummy; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_if {int /*<<< orphan*/  mac_addr; TYPE_1__* ndev; int /*<<< orphan*/  bsscfgidx; struct brcmf_pub* drvr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,int) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int brcmf_fil_iovar_data_set (struct brcmf_if*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct brcmf_if* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int brcmf_netdev_set_mac_address(struct net_device *ndev, void *addr)
{
	struct brcmf_if *ifp = netdev_priv(ndev);
	struct sockaddr *sa = (struct sockaddr *)addr;
	struct brcmf_pub *drvr = ifp->drvr;
	int err;

	brcmf_dbg(TRACE, "Enter, bsscfgidx=%d\n", ifp->bsscfgidx);

	err = brcmf_fil_iovar_data_set(ifp, "cur_etheraddr", sa->sa_data,
				       ETH_ALEN);
	if (err < 0) {
		bphy_err(drvr, "Setting cur_etheraddr failed, %d\n", err);
	} else {
		brcmf_dbg(TRACE, "updated to %pM\n", sa->sa_data);
		memcpy(ifp->mac_addr, sa->sa_data, ETH_ALEN);
		memcpy(ifp->ndev->dev_addr, ifp->mac_addr, ETH_ALEN);
	}
	return err;
}