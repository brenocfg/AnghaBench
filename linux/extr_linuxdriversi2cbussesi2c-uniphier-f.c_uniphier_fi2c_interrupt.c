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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct uniphier_fi2c_priv {int enabled_irqs; int flags; int len; int /*<<< orphan*/  comp; scalar_t__ membase; TYPE_1__ adap; int /*<<< orphan*/  error; } ;
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
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  uniphier_fi2c_clear_irqs (struct uniphier_fi2c_priv*) ; 
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

	irq_status = readl(priv->membase + UNIPHIER_FI2C_INT);

	dev_dbg(&priv->adap.dev,
		"interrupt: enabled_irqs=%04x, irq_status=%04x\n",
		priv->enabled_irqs, irq_status);

	if (irq_status & UNIPHIER_FI2C_INT_STOP)
		goto complete;

	if (unlikely(irq_status & UNIPHIER_FI2C_INT_AL)) {
		dev_dbg(&priv->adap.dev, "arbitration lost\n");
		priv->error = -EAGAIN;
		goto complete;
	}

	if (unlikely(irq_status & UNIPHIER_FI2C_INT_NA)) {
		dev_dbg(&priv->adap.dev, "could not get ACK\n");
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
		if (!priv->len)
			goto data_done;

		if (unlikely(priv->flags & UNIPHIER_FI2C_MANUAL_NACK)) {
			if (priv->len <= UNIPHIER_FI2C_FIFO_SIZE &&
			    !(priv->flags & UNIPHIER_FI2C_BYTE_WISE)) {
				dev_dbg(&priv->adap.dev,
					"enable read byte count IRQ\n");
				priv->enabled_irqs |= UNIPHIER_FI2C_INT_RB;
				uniphier_fi2c_set_irqs(priv);
				priv->flags |= UNIPHIER_FI2C_BYTE_WISE;
			}
			if (priv->len <= 1) {
				dev_dbg(&priv->adap.dev, "set NACK\n");
				writel(UNIPHIER_FI2C_CR_MST |
				       UNIPHIER_FI2C_CR_NACK,
				       priv->membase + UNIPHIER_FI2C_CR);
			}
		}

		goto handled;
	}

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
	uniphier_fi2c_clear_irqs(priv);

	return IRQ_HANDLED;
}