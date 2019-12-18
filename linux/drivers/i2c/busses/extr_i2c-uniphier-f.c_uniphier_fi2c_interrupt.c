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
struct uniphier_fi2c_priv {int enabled_irqs; int flags; int len; int /*<<< orphan*/  lock; int /*<<< orphan*/  comp; scalar_t__ membase; int /*<<< orphan*/  error; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int UNIPHIER_FI2C_BYTE_WISE ; 
 scalar_t__ UNIPHIER_FI2C_CR ; 
 int UNIPHIER_FI2C_CR_MST ; 
 int UNIPHIER_FI2C_CR_NACK ; 
 int UNIPHIER_FI2C_DEFER_STOP_COMP ; 
 int UNIPHIER_FI2C_FIFO_SIZE ; 
 scalar_t__ UNIPHIER_FI2C_INT ; 
 int UNIPHIER_FI2C_INT_AL ; 
 int UNIPHIER_FI2C_INT_NA ; 
 int UNIPHIER_FI2C_INT_RB ; 
 int UNIPHIER_FI2C_INT_RF ; 
 int UNIPHIER_FI2C_INT_STOP ; 
 int UNIPHIER_FI2C_INT_TE ; 
 int UNIPHIER_FI2C_MANUAL_NACK ; 
 int UNIPHIER_FI2C_RD ; 
 int UNIPHIER_FI2C_STOP ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uniphier_fi2c_clear_irqs (struct uniphier_fi2c_priv*,int) ; 
 int /*<<< orphan*/  uniphier_fi2c_drain_rxfifo (struct uniphier_fi2c_priv*) ; 
 int /*<<< orphan*/  uniphier_fi2c_fill_txfifo (struct uniphier_fi2c_priv*,int) ; 
 int /*<<< orphan*/  uniphier_fi2c_set_irqs (struct uniphier_fi2c_priv*) ; 
 int /*<<< orphan*/  uniphier_fi2c_stop (struct uniphier_fi2c_priv*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t uniphier_fi2c_interrupt(int irq, void *dev_id)
{
	struct uniphier_fi2c_priv *priv = dev_id;
	u32 irq_status;

	spin_lock(&priv->lock);

	irq_status = readl(priv->membase + UNIPHIER_FI2C_INT);
	irq_status &= priv->enabled_irqs;

	if (irq_status & UNIPHIER_FI2C_INT_STOP)
		goto complete;

	if (unlikely(irq_status & UNIPHIER_FI2C_INT_AL)) {
		priv->error = -EAGAIN;
		goto complete;
	}

	if (unlikely(irq_status & UNIPHIER_FI2C_INT_NA)) {
		priv->error = -ENXIO;
		if (priv->flags & UNIPHIER_FI2C_RD) {
			/*
			 * work around a hardware bug:
			 * The receive-completed interrupt is never set even if
			 * STOP condition is detected after the address phase
			 * of read transaction fails to get ACK.
			 * To avoid time-out error, we issue STOP here,
			 * but do not wait for its completion.
			 * It should be checked after exiting this handler.
			 */
			uniphier_fi2c_stop(priv);
			priv->flags |= UNIPHIER_FI2C_DEFER_STOP_COMP;
			goto complete;
		}
		goto stop;
	}

	if (irq_status & UNIPHIER_FI2C_INT_TE) {
		if (!priv->len)
			goto data_done;

		uniphier_fi2c_fill_txfifo(priv, false);
		goto handled;
	}

	if (irq_status & (UNIPHIER_FI2C_INT_RF | UNIPHIER_FI2C_INT_RB)) {
		uniphier_fi2c_drain_rxfifo(priv);
		/*
		 * If the number of bytes to read is multiple of the FIFO size
		 * (msg->len == 8, 16, 24, ...), the INT_RF bit is set a little
		 * earlier than INT_RB. We wait for INT_RB to confirm the
		 * completion of the current message.
		 */
		if (!priv->len && (irq_status & UNIPHIER_FI2C_INT_RB))
			goto data_done;

		if (unlikely(priv->flags & UNIPHIER_FI2C_MANUAL_NACK)) {
			if (priv->len <= UNIPHIER_FI2C_FIFO_SIZE &&
			    !(priv->flags & UNIPHIER_FI2C_BYTE_WISE)) {
				priv->enabled_irqs |= UNIPHIER_FI2C_INT_RB;
				uniphier_fi2c_set_irqs(priv);
				priv->flags |= UNIPHIER_FI2C_BYTE_WISE;
			}
			if (priv->len <= 1)
				writel(UNIPHIER_FI2C_CR_MST |
				       UNIPHIER_FI2C_CR_NACK,
				       priv->membase + UNIPHIER_FI2C_CR);
		}

		goto handled;
	}

	spin_unlock(&priv->lock);

	return IRQ_NONE;

data_done:
	if (priv->flags & UNIPHIER_FI2C_STOP) {
stop:
		uniphier_fi2c_stop(priv);
	} else {
complete:
		priv->enabled_irqs = 0;
		uniphier_fi2c_set_irqs(priv);
		complete(&priv->comp);
	}

handled:
	/*
	 * This controller makes a pause while any bit of the IRQ status is
	 * asserted. Clear the asserted bit to kick the controller just before
	 * exiting the handler.
	 */
	uniphier_fi2c_clear_irqs(priv, irq_status);

	spin_unlock(&priv->lock);

	return IRQ_HANDLED;
}