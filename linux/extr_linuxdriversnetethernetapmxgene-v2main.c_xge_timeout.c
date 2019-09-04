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
struct xge_pdata {int /*<<< orphan*/  napi; int /*<<< orphan*/  tx_ring; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMATXCTRL ; 
 int /*<<< orphan*/  DMATXSTATUS ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct xge_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  xge_free_pending_skb (struct net_device*) ; 
 int /*<<< orphan*/  xge_intr_disable (struct xge_pdata*) ; 
 int /*<<< orphan*/  xge_intr_enable (struct xge_pdata*) ; 
 int /*<<< orphan*/  xge_mac_enable (struct xge_pdata*) ; 
 int /*<<< orphan*/  xge_mac_init (struct xge_pdata*) ; 
 int /*<<< orphan*/  xge_setup_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xge_txc_poll (struct net_device*) ; 
 int /*<<< orphan*/  xge_update_tx_desc_addr (struct xge_pdata*) ; 
 int /*<<< orphan*/  xge_wr_csr (struct xge_pdata*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void xge_timeout(struct net_device *ndev)
{
	struct xge_pdata *pdata = netdev_priv(ndev);

	rtnl_lock();

	if (!netif_running(ndev))
		goto out;

	netif_stop_queue(ndev);
	xge_intr_disable(pdata);
	napi_disable(&pdata->napi);

	xge_wr_csr(pdata, DMATXCTRL, 0);
	xge_txc_poll(ndev);
	xge_free_pending_skb(ndev);
	xge_wr_csr(pdata, DMATXSTATUS, ~0U);

	xge_setup_desc(pdata->tx_ring);
	xge_update_tx_desc_addr(pdata);
	xge_mac_init(pdata);

	napi_enable(&pdata->napi);
	xge_intr_enable(pdata);
	xge_mac_enable(pdata);
	netif_start_queue(ndev);

out:
	rtnl_unlock();
}