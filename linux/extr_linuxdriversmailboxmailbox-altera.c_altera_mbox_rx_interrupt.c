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
struct mbox_chan {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  altera_mbox_rx_data (struct mbox_chan*) ; 

__attribute__((used)) static irqreturn_t altera_mbox_rx_interrupt(int irq, void *p)
{
	struct mbox_chan *chan = (struct mbox_chan *)p;

	altera_mbox_rx_data(chan);
	return IRQ_HANDLED;
}