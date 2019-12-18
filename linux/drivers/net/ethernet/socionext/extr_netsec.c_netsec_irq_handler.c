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
struct netsec_priv {int /*<<< orphan*/  napi; int /*<<< orphan*/  reglock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int NETSEC_IRQ_RX ; 
 int NETSEC_IRQ_TX ; 
 int /*<<< orphan*/  NETSEC_REG_INTEN_CLR ; 
 int /*<<< orphan*/  NETSEC_REG_NRM_RX_STATUS ; 
 int /*<<< orphan*/  NETSEC_REG_NRM_TX_STATUS ; 
 int /*<<< orphan*/  NETSEC_REG_TOP_STATUS ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int netsec_read (struct netsec_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netsec_write (struct netsec_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t netsec_irq_handler(int irq, void *dev_id)
{
	struct netsec_priv *priv = dev_id;
	u32 val, status = netsec_read(priv, NETSEC_REG_TOP_STATUS);
	unsigned long flags;

	/* Disable interrupts */
	if (status & NETSEC_IRQ_TX) {
		val = netsec_read(priv, NETSEC_REG_NRM_TX_STATUS);
		netsec_write(priv, NETSEC_REG_NRM_TX_STATUS, val);
	}
	if (status & NETSEC_IRQ_RX) {
		val = netsec_read(priv, NETSEC_REG_NRM_RX_STATUS);
		netsec_write(priv, NETSEC_REG_NRM_RX_STATUS, val);
	}

	spin_lock_irqsave(&priv->reglock, flags);
	netsec_write(priv, NETSEC_REG_INTEN_CLR, NETSEC_IRQ_RX | NETSEC_IRQ_TX);
	spin_unlock_irqrestore(&priv->reglock, flags);

	napi_schedule(&priv->napi);

	return IRQ_HANDLED;
}