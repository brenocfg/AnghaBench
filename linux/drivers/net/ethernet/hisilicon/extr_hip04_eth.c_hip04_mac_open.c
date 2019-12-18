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
struct net_device {int dummy; } ;
struct hip04_priv {int /*<<< orphan*/  napi; scalar_t__ phy; int /*<<< orphan*/ * rx_phys; int /*<<< orphan*/  dev; int /*<<< orphan*/ * rx_buf; scalar_t__ tx_tail; scalar_t__ tx_head; scalar_t__ rx_cnt_remaining; scalar_t__ rx_head; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EIO ; 
 int /*<<< orphan*/  RX_BUF_SIZE ; 
 int RX_DESC_NUM ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hip04_mac_enable (struct net_device*) ; 
 int /*<<< orphan*/  hip04_reset_ppe (struct hip04_priv*) ; 
 int /*<<< orphan*/  hip04_set_recv_desc (struct hip04_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct hip04_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_reset_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_start (scalar_t__) ; 

__attribute__((used)) static int hip04_mac_open(struct net_device *ndev)
{
	struct hip04_priv *priv = netdev_priv(ndev);
	int i;

	priv->rx_head = 0;
	priv->rx_cnt_remaining = 0;
	priv->tx_head = 0;
	priv->tx_tail = 0;
	hip04_reset_ppe(priv);

	for (i = 0; i < RX_DESC_NUM; i++) {
		dma_addr_t phys;

		phys = dma_map_single(priv->dev, priv->rx_buf[i],
				      RX_BUF_SIZE, DMA_FROM_DEVICE);
		if (dma_mapping_error(priv->dev, phys))
			return -EIO;

		priv->rx_phys[i] = phys;
		hip04_set_recv_desc(priv, phys);
	}

	if (priv->phy)
		phy_start(priv->phy);

	netdev_reset_queue(ndev);
	netif_start_queue(ndev);
	hip04_mac_enable(ndev);
	napi_enable(&priv->napi);

	return 0;
}