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
typedef  int u32 ;
struct mwl8k_priv {scalar_t__ pending_tx_pkts; scalar_t__ radio_on; int /*<<< orphan*/  fw_mutex; int /*<<< orphan*/ * hostcmd_wait; scalar_t__ regs; int /*<<< orphan*/  watchdog_ba_handle; int /*<<< orphan*/  watchdog_event_pending; int /*<<< orphan*/  poll_rx_task; int /*<<< orphan*/  poll_tx_task; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int MWL8K_A2H_INT_BA_WATCHDOG ; 
 int MWL8K_A2H_INT_OPC_DONE ; 
 int MWL8K_A2H_INT_QUEUE_EMPTY ; 
 int MWL8K_A2H_INT_RX_READY ; 
 int MWL8K_A2H_INT_TX_DONE ; 
 scalar_t__ MWL8K_HIU_A2H_INTERRUPT_STATUS ; 
 scalar_t__ MWL8K_HIU_A2H_INTERRUPT_STATUS_MASK ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_queue_work (struct ieee80211_hw*,int /*<<< orphan*/ *) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mwl8k_tx_start (struct mwl8k_priv*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mwl8k_interrupt(int irq, void *dev_id)
{
	struct ieee80211_hw *hw = dev_id;
	struct mwl8k_priv *priv = hw->priv;
	u32 status;

	status = ioread32(priv->regs + MWL8K_HIU_A2H_INTERRUPT_STATUS);
	if (!status)
		return IRQ_NONE;

	if (status & MWL8K_A2H_INT_TX_DONE) {
		status &= ~MWL8K_A2H_INT_TX_DONE;
		tasklet_schedule(&priv->poll_tx_task);
	}

	if (status & MWL8K_A2H_INT_RX_READY) {
		status &= ~MWL8K_A2H_INT_RX_READY;
		tasklet_schedule(&priv->poll_rx_task);
	}

	if (status & MWL8K_A2H_INT_BA_WATCHDOG) {
		iowrite32(~MWL8K_A2H_INT_BA_WATCHDOG,
			  priv->regs + MWL8K_HIU_A2H_INTERRUPT_STATUS_MASK);

		atomic_inc(&priv->watchdog_event_pending);
		status &= ~MWL8K_A2H_INT_BA_WATCHDOG;
		ieee80211_queue_work(hw, &priv->watchdog_ba_handle);
	}

	if (status)
		iowrite32(~status, priv->regs + MWL8K_HIU_A2H_INTERRUPT_STATUS);

	if (status & MWL8K_A2H_INT_OPC_DONE) {
		if (priv->hostcmd_wait != NULL)
			complete(priv->hostcmd_wait);
	}

	if (status & MWL8K_A2H_INT_QUEUE_EMPTY) {
		if (!mutex_is_locked(&priv->fw_mutex) &&
		    priv->radio_on && priv->pending_tx_pkts)
			mwl8k_tx_start(priv);
	}

	return IRQ_HANDLED;
}