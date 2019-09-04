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
struct hisi_femac_priv {scalar_t__ tx_fifo_used_cnt; int /*<<< orphan*/  rxq; int /*<<< orphan*/  dev; int /*<<< orphan*/  txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXQ_NUM ; 
 int /*<<< orphan*/  TXQ_NUM ; 
 int hisi_femac_init_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hisi_femac_init_tx_and_rx_queues(struct hisi_femac_priv *priv)
{
	int ret;

	ret = hisi_femac_init_queue(priv->dev, &priv->txq, TXQ_NUM);
	if (ret)
		return ret;

	ret = hisi_femac_init_queue(priv->dev, &priv->rxq, RXQ_NUM);
	if (ret)
		return ret;

	priv->tx_fifo_used_cnt = 0;

	return 0;
}