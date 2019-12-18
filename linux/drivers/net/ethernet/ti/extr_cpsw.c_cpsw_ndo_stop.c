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
struct net_device {int /*<<< orphan*/  mc; } ;
struct cpsw_priv {int /*<<< orphan*/  ndev; struct cpsw_common* cpsw; } ;
struct cpsw_common {int usage_count; int /*<<< orphan*/  dev; int /*<<< orphan*/  ale; int /*<<< orphan*/  dma; int /*<<< orphan*/  cpts; int /*<<< orphan*/  napi_tx; int /*<<< orphan*/  napi_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  __hw_addr_ref_unsync_dev (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpdma_ctlr_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_ale_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_destroy_xdp_rxqs (struct cpsw_common*) ; 
 int /*<<< orphan*/  cpsw_info (struct cpsw_priv*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cpsw_intr_disable (struct cpsw_common*) ; 
 scalar_t__ cpsw_need_resplit (struct cpsw_common*) ; 
 int /*<<< orphan*/  cpsw_purge_all_mc ; 
 int /*<<< orphan*/  cpsw_slave_stop ; 
 int /*<<< orphan*/  cpsw_split_res (struct cpsw_common*) ; 
 int /*<<< orphan*/  cpts_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  for_each_slave (struct cpsw_priv*,int /*<<< orphan*/ ,struct cpsw_common*) ; 
 int /*<<< orphan*/  ifdown ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct cpsw_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpsw_ndo_stop(struct net_device *ndev)
{
	struct cpsw_priv *priv = netdev_priv(ndev);
	struct cpsw_common *cpsw = priv->cpsw;

	cpsw_info(priv, ifdown, "shutting down cpsw device\n");
	__hw_addr_ref_unsync_dev(&ndev->mc, ndev, cpsw_purge_all_mc);
	netif_tx_stop_all_queues(priv->ndev);
	netif_carrier_off(priv->ndev);

	if (cpsw->usage_count <= 1) {
		napi_disable(&cpsw->napi_rx);
		napi_disable(&cpsw->napi_tx);
		cpts_unregister(cpsw->cpts);
		cpsw_intr_disable(cpsw);
		cpdma_ctlr_stop(cpsw->dma);
		cpsw_ale_stop(cpsw->ale);
		cpsw_destroy_xdp_rxqs(cpsw);
	}
	for_each_slave(priv, cpsw_slave_stop, cpsw);

	if (cpsw_need_resplit(cpsw))
		cpsw_split_res(cpsw);

	cpsw->usage_count--;
	pm_runtime_put_sync(cpsw->dev);
	return 0;
}