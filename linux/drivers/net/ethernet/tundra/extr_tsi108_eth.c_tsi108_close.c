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
typedef  int /*<<< orphan*/  tx_desc ;
struct tsi108_prv_data {int txhead; int txtail; int rxtail; int /*<<< orphan*/  txdma; int /*<<< orphan*/  txring; TYPE_1__* pdev; int /*<<< orphan*/  rxdma; int /*<<< orphan*/  rxring; scalar_t__ rxfree; struct sk_buff** rxskbs; int /*<<< orphan*/  irq_num; int /*<<< orphan*/  txfree; struct sk_buff** txskbs; int /*<<< orphan*/  timer; int /*<<< orphan*/  napi; } ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  rx_desc ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSI108_EC_INTMASK ; 
 int /*<<< orphan*/  TSI108_MAC_CFG1 ; 
 int TSI108_RXRING_LEN ; 
 int TSI108_TXRING_LEN ; 
 int /*<<< orphan*/  TSI_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct tsi108_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  tsi108_kill_phy (struct net_device*) ; 
 int /*<<< orphan*/  tsi108_stop_ethernet (struct net_device*) ; 

__attribute__((used)) static int tsi108_close(struct net_device *dev)
{
	struct tsi108_prv_data *data = netdev_priv(dev);

	netif_stop_queue(dev);
	napi_disable(&data->napi);

	del_timer_sync(&data->timer);

	tsi108_stop_ethernet(dev);
	tsi108_kill_phy(dev);
	TSI_WRITE(TSI108_EC_INTMASK, ~0);
	TSI_WRITE(TSI108_MAC_CFG1, 0);

	/* Check for any pending TX packets, and drop them. */

	while (!data->txfree || data->txhead != data->txtail) {
		int tx = data->txtail;
		struct sk_buff *skb;
		skb = data->txskbs[tx];
		data->txtail = (data->txtail + 1) % TSI108_TXRING_LEN;
		data->txfree++;
		dev_kfree_skb(skb);
	}

	free_irq(data->irq_num, dev);

	/* Discard the RX ring. */

	while (data->rxfree) {
		int rx = data->rxtail;
		struct sk_buff *skb;

		skb = data->rxskbs[rx];
		data->rxtail = (data->rxtail + 1) % TSI108_RXRING_LEN;
		data->rxfree--;
		dev_kfree_skb(skb);
	}

	dma_free_coherent(&data->pdev->dev,
			    TSI108_RXRING_LEN * sizeof(rx_desc),
			    data->rxring, data->rxdma);
	dma_free_coherent(&data->pdev->dev,
			    TSI108_TXRING_LEN * sizeof(tx_desc),
			    data->txring, data->txdma);

	return 0;
}