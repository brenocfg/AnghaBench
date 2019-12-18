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
struct TYPE_2__ {int flags; int /*<<< orphan*/  tx_failed; int /*<<< orphan*/  tx_lock; } ;
struct ath9k_htc_priv {TYPE_1__ tx; } ;

/* Variables and functions */
 int ATH9K_HTC_OP_TX_DRAIN ; 
 int /*<<< orphan*/  ath9k_htc_tx_drainq (struct ath9k_htc_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ath9k_tx_failed_tasklet(unsigned long data)
{
	struct ath9k_htc_priv *priv = (struct ath9k_htc_priv *)data;

	spin_lock(&priv->tx.tx_lock);
	if (priv->tx.flags & ATH9K_HTC_OP_TX_DRAIN) {
		spin_unlock(&priv->tx.tx_lock);
		return;
	}
	spin_unlock(&priv->tx.tx_lock);

	ath9k_htc_tx_drainq(priv, &priv->tx.tx_failed);
}