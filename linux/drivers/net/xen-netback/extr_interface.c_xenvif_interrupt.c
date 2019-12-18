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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  xenvif_rx_interrupt (int,void*) ; 
 int /*<<< orphan*/  xenvif_tx_interrupt (int,void*) ; 

irqreturn_t xenvif_interrupt(int irq, void *dev_id)
{
	xenvif_tx_interrupt(irq, dev_id);
	xenvif_rx_interrupt(irq, dev_id);

	return IRQ_HANDLED;
}