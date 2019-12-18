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
struct cc2520_private {TYPE_1__* spi; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_complete; scalar_t__ is_tx; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t cc2520_sfd_isr(int irq, void *data)
{
	struct cc2520_private *priv = data;
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);
	if (priv->is_tx) {
		priv->is_tx = 0;
		spin_unlock_irqrestore(&priv->lock, flags);
		dev_dbg(&priv->spi->dev, "SFD for TX\n");
		complete(&priv->tx_complete);
	} else {
		spin_unlock_irqrestore(&priv->lock, flags);
		dev_dbg(&priv->spi->dev, "SFD for RX\n");
	}

	return IRQ_HANDLED;
}