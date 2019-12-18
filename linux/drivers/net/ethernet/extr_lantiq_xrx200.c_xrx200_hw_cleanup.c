#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * skb; int /*<<< orphan*/  dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma; } ;
struct xrx200_priv {TYPE_2__ chan_rx; TYPE_1__ chan_tx; } ;

/* Variables and functions */
 int LTQ_DESC_NUM ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltq_dma_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xrx200_hw_cleanup(struct xrx200_priv *priv)
{
	int i;

	ltq_dma_free(&priv->chan_tx.dma);
	ltq_dma_free(&priv->chan_rx.dma);

	/* free the allocated RX ring */
	for (i = 0; i < LTQ_DESC_NUM; i++)
		dev_kfree_skb_any(priv->chan_rx.skb[i]);
}