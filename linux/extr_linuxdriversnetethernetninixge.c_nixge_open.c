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
struct phy_device {int dummy; } ;
struct nixge_priv {int /*<<< orphan*/  dma_err_tasklet; int /*<<< orphan*/  tx_irq; int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  napi; int /*<<< orphan*/  phy_mode; int /*<<< orphan*/  phy_node; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct nixge_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  nixge_device_reset (struct net_device*) ; 
 int /*<<< orphan*/  nixge_dma_err_handler ; 
 int /*<<< orphan*/  nixge_handle_link_change ; 
 int /*<<< orphan*/  nixge_rx_irq ; 
 int /*<<< orphan*/  nixge_tx_irq ; 
 struct phy_device* of_phy_connect (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_disconnect (struct phy_device*) ; 
 int /*<<< orphan*/  phy_start (struct phy_device*) ; 
 int /*<<< orphan*/  phy_stop (struct phy_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nixge_open(struct net_device *ndev)
{
	struct nixge_priv *priv = netdev_priv(ndev);
	struct phy_device *phy;
	int ret;

	nixge_device_reset(ndev);

	phy = of_phy_connect(ndev, priv->phy_node,
			     &nixge_handle_link_change, 0, priv->phy_mode);
	if (!phy)
		return -ENODEV;

	phy_start(phy);

	/* Enable tasklets for Axi DMA error handling */
	tasklet_init(&priv->dma_err_tasklet, nixge_dma_err_handler,
		     (unsigned long)priv);

	napi_enable(&priv->napi);

	/* Enable interrupts for Axi DMA Tx */
	ret = request_irq(priv->tx_irq, nixge_tx_irq, 0, ndev->name, ndev);
	if (ret)
		goto err_tx_irq;
	/* Enable interrupts for Axi DMA Rx */
	ret = request_irq(priv->rx_irq, nixge_rx_irq, 0, ndev->name, ndev);
	if (ret)
		goto err_rx_irq;

	netif_start_queue(ndev);

	return 0;

err_rx_irq:
	free_irq(priv->tx_irq, ndev);
err_tx_irq:
	phy_stop(phy);
	phy_disconnect(phy);
	tasklet_kill(&priv->dma_err_tasklet);
	netdev_err(ndev, "request_irq() failed\n");
	return ret;
}