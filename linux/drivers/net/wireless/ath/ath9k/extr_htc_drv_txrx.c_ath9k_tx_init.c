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
struct TYPE_2__ {int /*<<< orphan*/  tx_failed; int /*<<< orphan*/  data_vo_queue; int /*<<< orphan*/  data_vi_queue; int /*<<< orphan*/  data_bk_queue; int /*<<< orphan*/  data_be_queue; int /*<<< orphan*/  cab_ep_queue; int /*<<< orphan*/  mgmt_ep_queue; } ;
struct ath9k_htc_priv {TYPE_1__ tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

int ath9k_tx_init(struct ath9k_htc_priv *priv)
{
	skb_queue_head_init(&priv->tx.mgmt_ep_queue);
	skb_queue_head_init(&priv->tx.cab_ep_queue);
	skb_queue_head_init(&priv->tx.data_be_queue);
	skb_queue_head_init(&priv->tx.data_bk_queue);
	skb_queue_head_init(&priv->tx.data_vi_queue);
	skb_queue_head_init(&priv->tx.data_vo_queue);
	skb_queue_head_init(&priv->tx.tx_failed);
	return 0;
}