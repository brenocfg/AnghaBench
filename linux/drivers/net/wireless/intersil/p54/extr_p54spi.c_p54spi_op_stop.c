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
struct p54s_priv {scalar_t__ fw_state; int /*<<< orphan*/  work; int /*<<< orphan*/  mutex; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  tx_pending; } ;
struct ieee80211_hw {struct p54s_priv* priv; } ;

/* Variables and functions */
 scalar_t__ FW_STATE_OFF ; 
 scalar_t__ FW_STATE_READY ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p54spi_power_off (struct p54s_priv*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void p54spi_op_stop(struct ieee80211_hw *dev)
{
	struct p54s_priv *priv = dev->priv;
	unsigned long flags;

	mutex_lock(&priv->mutex);
	WARN_ON(priv->fw_state != FW_STATE_READY);

	p54spi_power_off(priv);
	spin_lock_irqsave(&priv->tx_lock, flags);
	INIT_LIST_HEAD(&priv->tx_pending);
	spin_unlock_irqrestore(&priv->tx_lock, flags);

	priv->fw_state = FW_STATE_OFF;
	mutex_unlock(&priv->mutex);

	cancel_work_sync(&priv->work);
}