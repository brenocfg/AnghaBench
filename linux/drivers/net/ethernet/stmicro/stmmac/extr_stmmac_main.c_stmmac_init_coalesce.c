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
struct stmmac_tx_queue {int /*<<< orphan*/  txtimer; } ;
struct stmmac_priv {struct stmmac_tx_queue* tx_queue; int /*<<< orphan*/  rx_coal_frames; int /*<<< orphan*/  tx_coal_timer; int /*<<< orphan*/  tx_coal_frames; TYPE_1__* plat; } ;
struct TYPE_2__ {size_t tx_queues_to_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  STMMAC_COAL_TX_TIMER ; 
 int /*<<< orphan*/  STMMAC_RX_FRAMES ; 
 int /*<<< orphan*/  STMMAC_TX_FRAMES ; 
 int /*<<< orphan*/  stmmac_tx_timer ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stmmac_init_coalesce(struct stmmac_priv *priv)
{
	u32 tx_channel_count = priv->plat->tx_queues_to_use;
	u32 chan;

	priv->tx_coal_frames = STMMAC_TX_FRAMES;
	priv->tx_coal_timer = STMMAC_COAL_TX_TIMER;
	priv->rx_coal_frames = STMMAC_RX_FRAMES;

	for (chan = 0; chan < tx_channel_count; chan++) {
		struct stmmac_tx_queue *tx_q = &priv->tx_queue[chan];

		timer_setup(&tx_q->txtimer, stmmac_tx_timer, 0);
	}
}