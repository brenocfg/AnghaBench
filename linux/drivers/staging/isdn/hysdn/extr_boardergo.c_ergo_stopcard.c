#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hysdn_lock; int /*<<< orphan*/  err_log_state; int /*<<< orphan*/  state; scalar_t__ iobase; scalar_t__ irq_enabled; } ;
typedef  TYPE_1__ hysdn_card ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_STATE_UNUSED ; 
 int /*<<< orphan*/  ERRLOG_STATE_OFF ; 
 unsigned char PCI9050_E1_RESET ; 
 scalar_t__ PCI9050_INTR_REG ; 
 unsigned char PCI9050_INTR_REG_EN1 ; 
 unsigned char PCI9050_INTR_REG_ENPCI ; 
 scalar_t__ PCI9050_USER_IO ; 
 unsigned char bytein (scalar_t__) ; 
 int /*<<< orphan*/  byteout (scalar_t__,unsigned char) ; 
 int /*<<< orphan*/  hycapi_capi_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  hysdn_net_release (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
ergo_stopcard(hysdn_card *card)
{
	unsigned long flags;
	unsigned char val;

	hysdn_net_release(card);	/* first release the net device if existing */
#ifdef CONFIG_HYSDN_CAPI
	hycapi_capi_stop(card);
#endif /* CONFIG_HYSDN_CAPI */
	spin_lock_irqsave(&card->hysdn_lock, flags);
	val = bytein(card->iobase + PCI9050_INTR_REG);	/* get actual value */
	val &= ~(PCI9050_INTR_REG_ENPCI | PCI9050_INTR_REG_EN1);	/* mask irq */
	byteout(card->iobase + PCI9050_INTR_REG, val);
	card->irq_enabled = 0;
	byteout(card->iobase + PCI9050_USER_IO, PCI9050_E1_RESET);	/* reset E1 processor */
	card->state = CARD_STATE_UNUSED;
	card->err_log_state = ERRLOG_STATE_OFF;		/* currently no log active */

	spin_unlock_irqrestore(&card->hysdn_lock, flags);
}