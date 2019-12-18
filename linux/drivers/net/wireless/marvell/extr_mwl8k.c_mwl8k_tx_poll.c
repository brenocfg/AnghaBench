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
struct mwl8k_priv {int /*<<< orphan*/  poll_tx_task; scalar_t__ regs; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/ * tx_wait; int /*<<< orphan*/  pending_tx_pkts; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MWL8K_A2H_INT_TX_DONE ; 
 scalar_t__ MWL8K_HIU_A2H_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int mwl8k_tx_queues (struct mwl8k_priv*) ; 
 scalar_t__ mwl8k_txq_reclaim (struct ieee80211_hw*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mwl8k_tx_poll(unsigned long data)
{
	struct ieee80211_hw *hw = (struct ieee80211_hw *)data;
	struct mwl8k_priv *priv = hw->priv;
	int limit;
	int i;

	limit = 32;

	spin_lock(&priv->tx_lock);

	for (i = 0; i < mwl8k_tx_queues(priv); i++)
		limit -= mwl8k_txq_reclaim(hw, i, limit, 0);

	if (!priv->pending_tx_pkts && priv->tx_wait != NULL) {
		complete(priv->tx_wait);
		priv->tx_wait = NULL;
	}

	spin_unlock(&priv->tx_lock);

	if (limit) {
		writel(~MWL8K_A2H_INT_TX_DONE,
		       priv->regs + MWL8K_HIU_A2H_INTERRUPT_STATUS);
	} else {
		tasklet_schedule(&priv->poll_tx_task);
	}
}