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
struct xge_pdata {int /*<<< orphan*/  napi; } ;
struct net_device {int /*<<< orphan*/  phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct xge_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xge_delete_desc_rings (struct net_device*) ; 
 int /*<<< orphan*/  xge_free_irq (struct net_device*) ; 
 int /*<<< orphan*/  xge_intr_disable (struct xge_pdata*) ; 
 int /*<<< orphan*/  xge_mac_disable (struct xge_pdata*) ; 

__attribute__((used)) static int xge_close(struct net_device *ndev)
{
	struct xge_pdata *pdata = netdev_priv(ndev);

	netif_stop_queue(ndev);
	xge_mac_disable(pdata);
	phy_stop(ndev->phydev);

	xge_intr_disable(pdata);
	xge_free_irq(ndev);
	napi_disable(&pdata->napi);
	xge_delete_desc_rings(ndev);

	return 0;
}