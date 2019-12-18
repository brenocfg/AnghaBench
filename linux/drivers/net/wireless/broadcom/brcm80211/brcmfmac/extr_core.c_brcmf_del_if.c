#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct brcmf_pub {size_t* if2bss; struct brcmf_if** iflist; } ;
struct brcmf_if {int ifidx; TYPE_1__* ndev; int /*<<< orphan*/  ndoffload_work; int /*<<< orphan*/  multicast_work; } ;
typedef  size_t s32 ;
struct TYPE_4__ {int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 size_t BRCMF_BSSIDX_INVALID ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,size_t) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,size_t,int) ; 
 int /*<<< orphan*/  brcmf_net_detach (TYPE_1__*,int) ; 
 int /*<<< orphan*/  brcmf_netdev_ops_pri ; 
 int /*<<< orphan*/  brcmf_netdev_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  brcmf_p2p_ifp_removed (struct brcmf_if*,int) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct brcmf_if*) ; 
 int /*<<< orphan*/  netif_stop_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static void brcmf_del_if(struct brcmf_pub *drvr, s32 bsscfgidx,
			 bool rtnl_locked)
{
	struct brcmf_if *ifp;
	int ifidx;

	ifp = drvr->iflist[bsscfgidx];
	if (!ifp) {
		bphy_err(drvr, "Null interface, bsscfgidx=%d\n", bsscfgidx);
		return;
	}
	brcmf_dbg(TRACE, "Enter, bsscfgidx=%d, ifidx=%d\n", bsscfgidx,
		  ifp->ifidx);
	ifidx = ifp->ifidx;

	if (ifp->ndev) {
		if (bsscfgidx == 0) {
			if (ifp->ndev->netdev_ops == &brcmf_netdev_ops_pri) {
				rtnl_lock();
				brcmf_netdev_stop(ifp->ndev);
				rtnl_unlock();
			}
		} else {
			netif_stop_queue(ifp->ndev);
		}

		if (ifp->ndev->netdev_ops == &brcmf_netdev_ops_pri) {
			cancel_work_sync(&ifp->multicast_work);
			cancel_work_sync(&ifp->ndoffload_work);
		}
		brcmf_net_detach(ifp->ndev, rtnl_locked);
	} else {
		/* Only p2p device interfaces which get dynamically created
		 * end up here. In this case the p2p module should be informed
		 * about the removal of the interface within the firmware. If
		 * not then p2p commands towards the firmware will cause some
		 * serious troublesome side effects. The p2p module will clean
		 * up the ifp if needed.
		 */
		brcmf_p2p_ifp_removed(ifp, rtnl_locked);
		kfree(ifp);
	}

	drvr->iflist[bsscfgidx] = NULL;
	if (drvr->if2bss[ifidx] == bsscfgidx)
		drvr->if2bss[ifidx] = BRCMF_BSSIDX_INVALID;
}