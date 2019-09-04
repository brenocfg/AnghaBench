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
struct net_device {int dummy; } ;
struct ltq_etop_priv {int dummy; } ;
struct TYPE_2__ {size_t desc; scalar_t__ irq; } ;
struct ltq_etop_chan {TYPE_1__ dma; int /*<<< orphan*/ * skb; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 scalar_t__ IS_RX (int /*<<< orphan*/ ) ; 
 int LTQ_DESC_NUM ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct ltq_etop_priv*) ; 
 int /*<<< orphan*/  ltq_dma_free (TYPE_1__*) ; 
 struct ltq_etop_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
ltq_etop_free_channel(struct net_device *dev, struct ltq_etop_chan *ch)
{
	struct ltq_etop_priv *priv = netdev_priv(dev);

	ltq_dma_free(&ch->dma);
	if (ch->dma.irq)
		free_irq(ch->dma.irq, priv);
	if (IS_RX(ch->idx)) {
		int desc;
		for (desc = 0; desc < LTQ_DESC_NUM; desc++)
			dev_kfree_skb_any(ch->skb[ch->dma.desc]);
	}
}