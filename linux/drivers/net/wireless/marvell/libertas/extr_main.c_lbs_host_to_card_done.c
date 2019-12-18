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
struct lbs_private {scalar_t__ tx_pending_len; int /*<<< orphan*/  driver_lock; int /*<<< orphan*/  waitq; int /*<<< orphan*/  wakeup_dev_required; int /*<<< orphan*/  cur_cmd; int /*<<< orphan*/  dnld_sent; int /*<<< orphan*/  tx_lockup_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DNLD_RES_RECEIVED ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void lbs_host_to_card_done(struct lbs_private *priv)
{
	unsigned long flags;

	spin_lock_irqsave(&priv->driver_lock, flags);
	del_timer(&priv->tx_lockup_timer);

	priv->dnld_sent = DNLD_RES_RECEIVED;

	/* Wake main thread if commands are pending */
	if (!priv->cur_cmd || priv->tx_pending_len > 0) {
		if (!priv->wakeup_dev_required)
			wake_up(&priv->waitq);
	}

	spin_unlock_irqrestore(&priv->driver_lock, flags);
}