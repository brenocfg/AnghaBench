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
struct xge_pdata {int /*<<< orphan*/  rx_ring; int /*<<< orphan*/  tx_ring; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct xge_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  xge_delete_desc_ring (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xge_free_buffers (struct net_device*) ; 
 int /*<<< orphan*/  xge_rx_poll (struct net_device*,int) ; 
 int /*<<< orphan*/  xge_txc_poll (struct net_device*) ; 

__attribute__((used)) static void xge_delete_desc_rings(struct net_device *ndev)
{
	struct xge_pdata *pdata = netdev_priv(ndev);

	xge_txc_poll(ndev);
	xge_delete_desc_ring(ndev, pdata->tx_ring);

	xge_rx_poll(ndev, 64);
	xge_free_buffers(ndev);
	xge_delete_desc_ring(ndev, pdata->rx_ring);
}