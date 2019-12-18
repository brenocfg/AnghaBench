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
struct mt76_dev {int /*<<< orphan*/ * napi; int /*<<< orphan*/ * rx_skb; int /*<<< orphan*/ * q_rx; int /*<<< orphan*/  napi_dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_dummy_netdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76_dma_rx_fill (struct mt76_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76_dma_rx_poll ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mt76_dma_init(struct mt76_dev *dev)
{
	int i;

	init_dummy_netdev(&dev->napi_dev);

	for (i = 0; i < ARRAY_SIZE(dev->q_rx); i++) {
		netif_napi_add(&dev->napi_dev, &dev->napi[i], mt76_dma_rx_poll,
			       64);
		mt76_dma_rx_fill(dev, &dev->q_rx[i]);
		skb_queue_head_init(&dev->rx_skb[i]);
		napi_enable(&dev->napi[i]);
	}

	return 0;
}