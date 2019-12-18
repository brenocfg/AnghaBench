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
typedef  int u32 ;
struct stmmac_priv {TYPE_1__* plat; int /*<<< orphan*/  hw; } ;
struct TYPE_2__ {int rx_queues_to_use; int tx_queues_to_use; int /*<<< orphan*/  tx_sched_algorithm; int /*<<< orphan*/  rx_sched_algorithm; } ;

/* Variables and functions */
 int /*<<< orphan*/  stmmac_configure_cbs (struct stmmac_priv*) ; 
 int /*<<< orphan*/  stmmac_mac_config_rss (struct stmmac_priv*) ; 
 int /*<<< orphan*/  stmmac_mac_config_rx_queues_prio (struct stmmac_priv*) ; 
 int /*<<< orphan*/  stmmac_mac_config_rx_queues_routing (struct stmmac_priv*) ; 
 int /*<<< orphan*/  stmmac_mac_config_tx_queues_prio (struct stmmac_priv*) ; 
 int /*<<< orphan*/  stmmac_mac_enable_rx_queues (struct stmmac_priv*) ; 
 int /*<<< orphan*/  stmmac_prog_mtl_rx_algorithms (struct stmmac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmmac_prog_mtl_tx_algorithms (struct stmmac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmmac_rx_queue_dma_chan_map (struct stmmac_priv*) ; 
 int /*<<< orphan*/  stmmac_set_tx_queue_weight (struct stmmac_priv*) ; 

__attribute__((used)) static void stmmac_mtl_configuration(struct stmmac_priv *priv)
{
	u32 rx_queues_count = priv->plat->rx_queues_to_use;
	u32 tx_queues_count = priv->plat->tx_queues_to_use;

	if (tx_queues_count > 1)
		stmmac_set_tx_queue_weight(priv);

	/* Configure MTL RX algorithms */
	if (rx_queues_count > 1)
		stmmac_prog_mtl_rx_algorithms(priv, priv->hw,
				priv->plat->rx_sched_algorithm);

	/* Configure MTL TX algorithms */
	if (tx_queues_count > 1)
		stmmac_prog_mtl_tx_algorithms(priv, priv->hw,
				priv->plat->tx_sched_algorithm);

	/* Configure CBS in AVB TX queues */
	if (tx_queues_count > 1)
		stmmac_configure_cbs(priv);

	/* Map RX MTL to DMA channels */
	stmmac_rx_queue_dma_chan_map(priv);

	/* Enable MAC RX Queues */
	stmmac_mac_enable_rx_queues(priv);

	/* Set RX priorities */
	if (rx_queues_count > 1)
		stmmac_mac_config_rx_queues_prio(priv);

	/* Set TX priorities */
	if (tx_queues_count > 1)
		stmmac_mac_config_tx_queues_prio(priv);

	/* Set RX routing */
	if (rx_queues_count > 1)
		stmmac_mac_config_rx_queues_routing(priv);

	/* Receive Side Scaling */
	if (rx_queues_count > 1)
		stmmac_mac_config_rss(priv);
}