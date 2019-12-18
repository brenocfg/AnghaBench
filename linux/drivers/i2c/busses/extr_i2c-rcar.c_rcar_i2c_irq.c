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
struct rcar_i2c_priv {int flags; int /*<<< orphan*/  wait; int /*<<< orphan*/  msgs_left; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ICMCR ; 
 int /*<<< orphan*/  ICMIER ; 
 int /*<<< orphan*/  ICMSR ; 
 int ID_ARBLOST ; 
 int ID_DONE ; 
 int ID_NACK ; 
 int ID_P_REP_AFTER_RD ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int MAL ; 
 int MNR ; 
 int MST ; 
 int RCAR_BUS_MASK_DATA ; 
 int RCAR_IRQ_STOP ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  rcar_i2c_irq_recv (struct rcar_i2c_priv*,int) ; 
 int /*<<< orphan*/  rcar_i2c_irq_send (struct rcar_i2c_priv*,int) ; 
 scalar_t__ rcar_i2c_is_recv (struct rcar_i2c_priv*) ; 
 int rcar_i2c_read (struct rcar_i2c_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ rcar_i2c_slave_irq (struct rcar_i2c_priv*) ; 
 int /*<<< orphan*/  rcar_i2c_write (struct rcar_i2c_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t rcar_i2c_irq(int irq, void *ptr)
{
	struct rcar_i2c_priv *priv = ptr;
	u32 msr, val;

	/* Clear START or STOP immediately, except for REPSTART after read */
	if (likely(!(priv->flags & ID_P_REP_AFTER_RD))) {
		val = rcar_i2c_read(priv, ICMCR);
		rcar_i2c_write(priv, ICMCR, val & RCAR_BUS_MASK_DATA);
	}

	msr = rcar_i2c_read(priv, ICMSR);

	/* Only handle interrupts that are currently enabled */
	msr &= rcar_i2c_read(priv, ICMIER);
	if (!msr) {
		if (rcar_i2c_slave_irq(priv))
			return IRQ_HANDLED;

		return IRQ_NONE;
	}

	/* Arbitration lost */
	if (msr & MAL) {
		priv->flags |= ID_DONE | ID_ARBLOST;
		goto out;
	}

	/* Nack */
	if (msr & MNR) {
		/* HW automatically sends STOP after received NACK */
		rcar_i2c_write(priv, ICMIER, RCAR_IRQ_STOP);
		priv->flags |= ID_NACK;
		goto out;
	}

	/* Stop */
	if (msr & MST) {
		priv->msgs_left--; /* The last message also made it */
		priv->flags |= ID_DONE;
		goto out;
	}

	if (rcar_i2c_is_recv(priv))
		rcar_i2c_irq_recv(priv, msr);
	else
		rcar_i2c_irq_send(priv, msr);

out:
	if (priv->flags & ID_DONE) {
		rcar_i2c_write(priv, ICMIER, 0);
		rcar_i2c_write(priv, ICMSR, 0);
		wake_up(&priv->wait);
	}

	return IRQ_HANDLED;
}