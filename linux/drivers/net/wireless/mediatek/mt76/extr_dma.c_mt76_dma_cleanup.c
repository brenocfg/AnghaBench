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
struct mt76_dev {int /*<<< orphan*/ * q_rx; int /*<<< orphan*/ * napi; int /*<<< orphan*/ * q_tx; int /*<<< orphan*/  tx_napi; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76_dma_rx_cleanup (struct mt76_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76_dma_tx_cleanup (struct mt76_dev*,int,int) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 

void mt76_dma_cleanup(struct mt76_dev *dev)
{
	int i;

	netif_napi_del(&dev->tx_napi);
	for (i = 0; i < ARRAY_SIZE(dev->q_tx); i++)
		mt76_dma_tx_cleanup(dev, i, true);

	for (i = 0; i < ARRAY_SIZE(dev->q_rx); i++) {
		netif_napi_del(&dev->napi[i]);
		mt76_dma_rx_cleanup(dev, &dev->q_rx[i]);
	}
}