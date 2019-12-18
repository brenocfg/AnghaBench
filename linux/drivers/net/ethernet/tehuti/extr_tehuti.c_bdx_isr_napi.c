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
struct net_device {int dummy; } ;
struct bdx_priv {int /*<<< orphan*/  napi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int IR_EXTRA ; 
 int IR_RUN ; 
 int IR_RX_DESC_0 ; 
 int IR_TX_FREE_0 ; 
 int READ_REG (struct bdx_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bdx_enable_interrupts (struct bdx_priv*) ; 
 int /*<<< orphan*/  bdx_isr_extra (struct bdx_priv*,int) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct bdx_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  regISR ; 
 int /*<<< orphan*/  regRXD_WPTR_0 ; 
 int /*<<< orphan*/  regTXF_WPTR_0 ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t bdx_isr_napi(int irq, void *dev)
{
	struct net_device *ndev = dev;
	struct bdx_priv *priv = netdev_priv(ndev);
	u32 isr;

	ENTER;
	isr = (READ_REG(priv, regISR) & IR_RUN);
	if (unlikely(!isr)) {
		bdx_enable_interrupts(priv);
		return IRQ_NONE;	/* Not our interrupt */
	}

	if (isr & IR_EXTRA)
		bdx_isr_extra(priv, isr);

	if (isr & (IR_RX_DESC_0 | IR_TX_FREE_0)) {
		if (likely(napi_schedule_prep(&priv->napi))) {
			__napi_schedule(&priv->napi);
			RET(IRQ_HANDLED);
		} else {
			/* NOTE: we get here if intr has slipped into window
			 * between these lines in bdx_poll:
			 *    bdx_enable_interrupts(priv);
			 *    return 0;
			 * currently intrs are disabled (since we read ISR),
			 * and we have failed to register next poll.
			 * so we read the regs to trigger chip
			 * and allow further interupts. */
			READ_REG(priv, regTXF_WPTR_0);
			READ_REG(priv, regRXD_WPTR_0);
		}
	}

	bdx_enable_interrupts(priv);
	RET(IRQ_HANDLED);
}