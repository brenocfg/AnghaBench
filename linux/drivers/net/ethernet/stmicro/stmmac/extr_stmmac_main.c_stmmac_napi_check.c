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
struct stmmac_priv {TYPE_1__* plat; int /*<<< orphan*/  ioaddr; struct stmmac_channel* channel; int /*<<< orphan*/  xstats; } ;
struct stmmac_channel {int /*<<< orphan*/  tx_napi; int /*<<< orphan*/  rx_napi; } ;
struct TYPE_2__ {size_t rx_queues_to_use; size_t tx_queues_to_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  __napi_schedule_irqoff (int /*<<< orphan*/ *) ; 
 int handle_rx ; 
 int handle_tx ; 
 int /*<<< orphan*/  napi_schedule_irqoff (int /*<<< orphan*/ *) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmmac_disable_dma_irq (struct stmmac_priv*,int /*<<< orphan*/ ,size_t) ; 
 int stmmac_dma_interrupt_status (struct stmmac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int stmmac_napi_check(struct stmmac_priv *priv, u32 chan)
{
	int status = stmmac_dma_interrupt_status(priv, priv->ioaddr,
						 &priv->xstats, chan);
	struct stmmac_channel *ch = &priv->channel[chan];

	if ((status & handle_rx) && (chan < priv->plat->rx_queues_to_use)) {
		if (napi_schedule_prep(&ch->rx_napi)) {
			stmmac_disable_dma_irq(priv, priv->ioaddr, chan);
			__napi_schedule_irqoff(&ch->rx_napi);
			status |= handle_tx;
		}
	}

	if ((status & handle_tx) && (chan < priv->plat->tx_queues_to_use))
		napi_schedule_irqoff(&ch->tx_napi);

	return status;
}