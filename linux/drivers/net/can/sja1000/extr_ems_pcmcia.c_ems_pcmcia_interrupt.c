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
struct net_device {int dummy; } ;
struct ems_pcmcia_card {int channels; struct net_device** net_dev; int /*<<< orphan*/  base_addr; } ;
typedef  scalar_t__ irqreturn_t ;

/* Variables and functions */
 scalar_t__ IRQ_HANDLED ; 
 scalar_t__ IRQ_NONE ; 
 int readw (int /*<<< orphan*/ ) ; 
 scalar_t__ sja1000_interrupt (int,struct net_device*) ; 

__attribute__((used)) static irqreturn_t ems_pcmcia_interrupt(int irq, void *dev_id)
{
	struct ems_pcmcia_card *card = dev_id;
	struct net_device *dev;
	irqreturn_t retval = IRQ_NONE;
	int i, again;

	/* Card not present */
	if (readw(card->base_addr) != 0xAA55)
		return IRQ_HANDLED;

	do {
		again = 0;

		/* Check interrupt for each channel */
		for (i = 0; i < card->channels; i++) {
			dev = card->net_dev[i];
			if (!dev)
				continue;

			if (sja1000_interrupt(irq, dev) == IRQ_HANDLED)
				again = 1;
		}
		/* At least one channel handled the interrupt */
		if (again)
			retval = IRQ_HANDLED;

	} while (again);

	return retval;
}