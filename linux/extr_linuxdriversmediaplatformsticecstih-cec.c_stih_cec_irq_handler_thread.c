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
struct stih_cec {int irq_status; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CEC_RX_DONE_STS ; 
 int CEC_TX_DONE_STS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  stih_rx_done (struct stih_cec*,int) ; 
 int /*<<< orphan*/  stih_tx_done (struct stih_cec*,int) ; 

__attribute__((used)) static irqreturn_t stih_cec_irq_handler_thread(int irq, void *priv)
{
	struct stih_cec *cec = priv;

	if (cec->irq_status & CEC_TX_DONE_STS)
		stih_tx_done(cec, cec->irq_status);

	if (cec->irq_status & CEC_RX_DONE_STS)
		stih_rx_done(cec, cec->irq_status);

	cec->irq_status = 0;

	return IRQ_HANDLED;
}