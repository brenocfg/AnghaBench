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
struct rcar_i2c_priv {int pos; int flags; struct i2c_msg* msg; } ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMCR ; 
 int /*<<< orphan*/  ICMSR ; 
 int /*<<< orphan*/  ICRXTX ; 
 int ID_LAST_MSG ; 
 int ID_P_REP_AFTER_RD ; 
 int MAT ; 
 int MDR ; 
 int /*<<< orphan*/  RCAR_BUS_PHASE_START ; 
 int /*<<< orphan*/  RCAR_BUS_PHASE_STOP ; 
 int /*<<< orphan*/  RCAR_IRQ_ACK_RECV ; 
 int /*<<< orphan*/  rcar_i2c_dma (struct rcar_i2c_priv*) ; 
 int /*<<< orphan*/  rcar_i2c_next_msg (struct rcar_i2c_priv*) ; 
 int /*<<< orphan*/  rcar_i2c_read (struct rcar_i2c_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_i2c_write (struct rcar_i2c_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcar_i2c_irq_recv(struct rcar_i2c_priv *priv, u32 msr)
{
	struct i2c_msg *msg = priv->msg;

	/* FIXME: sometimes, unknown interrupt happened. Do nothing */
	if (!(msr & MDR))
		return;

	if (msr & MAT) {
		/*
		 * Address transfer phase finished, but no data at this point.
		 * Try to use DMA to receive data.
		 */
		rcar_i2c_dma(priv);
	} else if (priv->pos < msg->len) {
		/* get received data */
		msg->buf[priv->pos] = rcar_i2c_read(priv, ICRXTX);
		priv->pos++;
	}

	/* If next received data is the _LAST_, go to new phase. */
	if (priv->pos + 1 == msg->len) {
		if (priv->flags & ID_LAST_MSG) {
			rcar_i2c_write(priv, ICMCR, RCAR_BUS_PHASE_STOP);
		} else {
			rcar_i2c_write(priv, ICMCR, RCAR_BUS_PHASE_START);
			priv->flags |= ID_P_REP_AFTER_RD;
		}
	}

	if (priv->pos == msg->len && !(priv->flags & ID_LAST_MSG))
		rcar_i2c_next_msg(priv);
	else
		rcar_i2c_write(priv, ICMSR, RCAR_IRQ_ACK_RECV);
}