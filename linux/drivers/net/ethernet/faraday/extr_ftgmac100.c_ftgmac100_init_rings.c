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
struct ftgmac100_txdes {int /*<<< orphan*/  txdes0; } ;
struct ftgmac100_rxdes {int /*<<< orphan*/  rxdes0; int /*<<< orphan*/  rxdes3; } ;
struct ftgmac100 {int rx_q_entries; int new_rx_q_entries; int tx_q_entries; int new_tx_q_entries; int /*<<< orphan*/  txdes0_edotr_mask; struct ftgmac100_txdes* txdes; int /*<<< orphan*/  rxdes0_edorr_mask; int /*<<< orphan*/  rx_scratch_dma; struct ftgmac100_rxdes* rxdes; } ;

/* Variables and functions */
 int MIN_RX_QUEUE_ENTRIES ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ftgmac100_init_rings(struct ftgmac100 *priv)
{
	struct ftgmac100_rxdes *rxdes = NULL;
	struct ftgmac100_txdes *txdes = NULL;
	int i;

	/* Update entries counts */
	priv->rx_q_entries = priv->new_rx_q_entries;
	priv->tx_q_entries = priv->new_tx_q_entries;

	if (WARN_ON(priv->rx_q_entries < MIN_RX_QUEUE_ENTRIES))
		return;

	/* Initialize RX ring */
	for (i = 0; i < priv->rx_q_entries; i++) {
		rxdes = &priv->rxdes[i];
		rxdes->rxdes0 = 0;
		rxdes->rxdes3 = cpu_to_le32(priv->rx_scratch_dma);
	}
	/* Mark the end of the ring */
	rxdes->rxdes0 |= cpu_to_le32(priv->rxdes0_edorr_mask);

	if (WARN_ON(priv->tx_q_entries < MIN_RX_QUEUE_ENTRIES))
		return;

	/* Initialize TX ring */
	for (i = 0; i < priv->tx_q_entries; i++) {
		txdes = &priv->txdes[i];
		txdes->txdes0 = 0;
	}
	txdes->txdes0 |= cpu_to_le32(priv->txdes0_edotr_mask);
}