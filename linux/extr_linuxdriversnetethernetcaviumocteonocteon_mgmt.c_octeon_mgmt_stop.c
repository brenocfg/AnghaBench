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
struct octeon_mgmt {int /*<<< orphan*/  tx_ring; int /*<<< orphan*/  tx_ring_handle; int /*<<< orphan*/  dev; int /*<<< orphan*/  rx_ring; int /*<<< orphan*/  rx_ring_handle; int /*<<< orphan*/  rx_list; int /*<<< orphan*/  tx_list; int /*<<< orphan*/  irq; int /*<<< orphan*/  napi; } ;
struct net_device {scalar_t__ phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  OCTEON_MGMT_RX_RING_SIZE ; 
 int /*<<< orphan*/  OCTEON_MGMT_TX_RING_SIZE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct octeon_mgmt* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  octeon_mgmt_reset_hw (struct octeon_mgmt*) ; 
 int /*<<< orphan*/  phy_disconnect (scalar_t__) ; 
 int /*<<< orphan*/  ring_size_to_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int octeon_mgmt_stop(struct net_device *netdev)
{
	struct octeon_mgmt *p = netdev_priv(netdev);

	napi_disable(&p->napi);
	netif_stop_queue(netdev);

	if (netdev->phydev)
		phy_disconnect(netdev->phydev);

	netif_carrier_off(netdev);

	octeon_mgmt_reset_hw(p);

	free_irq(p->irq, netdev);

	/* dma_unmap is a nop on Octeon, so just free everything.  */
	skb_queue_purge(&p->tx_list);
	skb_queue_purge(&p->rx_list);

	dma_unmap_single(p->dev, p->rx_ring_handle,
			 ring_size_to_bytes(OCTEON_MGMT_RX_RING_SIZE),
			 DMA_BIDIRECTIONAL);
	kfree(p->rx_ring);

	dma_unmap_single(p->dev, p->tx_ring_handle,
			 ring_size_to_bytes(OCTEON_MGMT_TX_RING_SIZE),
			 DMA_BIDIRECTIONAL);
	kfree(p->tx_ring);

	return 0;
}