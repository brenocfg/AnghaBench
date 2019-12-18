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
typedef  size_t u32 ;
struct stmmac_tx_queue {scalar_t__ mss; scalar_t__ dirty_tx; scalar_t__ cur_tx; } ;
struct stmmac_rx_queue {scalar_t__ dirty_rx; scalar_t__ cur_rx; } ;
struct stmmac_priv {struct stmmac_tx_queue* tx_queue; struct stmmac_rx_queue* rx_queue; TYPE_1__* plat; } ;
struct TYPE_2__ {size_t rx_queues_to_use; size_t tx_queues_to_use; } ;

/* Variables and functions */

__attribute__((used)) static void stmmac_reset_queues_param(struct stmmac_priv *priv)
{
	u32 rx_cnt = priv->plat->rx_queues_to_use;
	u32 tx_cnt = priv->plat->tx_queues_to_use;
	u32 queue;

	for (queue = 0; queue < rx_cnt; queue++) {
		struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];

		rx_q->cur_rx = 0;
		rx_q->dirty_rx = 0;
	}

	for (queue = 0; queue < tx_cnt; queue++) {
		struct stmmac_tx_queue *tx_q = &priv->tx_queue[queue];

		tx_q->cur_tx = 0;
		tx_q->dirty_tx = 0;
		tx_q->mss = 0;
	}
}