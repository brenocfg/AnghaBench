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
struct timer_list {int dummy; } ;
struct lbs_private {int /*<<< orphan*/  driver_lock; int /*<<< orphan*/  waitq; int /*<<< orphan*/  dnld_sent; int /*<<< orphan*/  (* reset_card ) (struct lbs_private*) ;int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DNLD_RES_RECEIVED ; 
 struct lbs_private* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 struct lbs_private* priv ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct lbs_private*) ; 
 int /*<<< orphan*/  tx_lockup_timer ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lbs_tx_lockup_handler(struct timer_list *t)
{
	struct lbs_private *priv = from_timer(priv, t, tx_lockup_timer);
	unsigned long flags;

	spin_lock_irqsave(&priv->driver_lock, flags);

	netdev_info(priv->dev, "TX lockup detected\n");
	if (priv->reset_card)
		priv->reset_card(priv);

	priv->dnld_sent = DNLD_RES_RECEIVED;
	wake_up_interruptible(&priv->waitq);

	spin_unlock_irqrestore(&priv->driver_lock, flags);
}