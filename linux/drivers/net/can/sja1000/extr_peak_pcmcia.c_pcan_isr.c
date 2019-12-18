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
struct pcan_pccard {int chan_count; TYPE_1__* channel; } ;
struct net_device {int dummy; } ;
typedef  scalar_t__ irqreturn_t ;
struct TYPE_2__ {struct net_device* netdev; } ;

/* Variables and functions */
 scalar_t__ IRQ_HANDLED ; 
 scalar_t__ IRQ_NONE ; 
 int PCC_ISR_MAX_LOOP ; 
 int /*<<< orphan*/  pcan_pccard_present (struct pcan_pccard*) ; 
 scalar_t__ sja1000_interrupt (int,struct net_device*) ; 

__attribute__((used)) static irqreturn_t pcan_isr(int irq, void *dev_id)
{
	struct pcan_pccard *card = dev_id;
	int irq_handled;

	/* prevent from infinite loop */
	for (irq_handled = 0; irq_handled < PCC_ISR_MAX_LOOP; irq_handled++) {
		/* handle shared interrupt and next loop */
		int nothing_to_handle = 1;
		int i;

		/* check interrupt for each channel */
		for (i = 0; i < card->chan_count; i++) {
			struct net_device *netdev;

			/*
			 * check whether the card is present before calling
			 * sja1000_interrupt() to speed up hotplug detection
			 */
			if (!pcan_pccard_present(card)) {
				/* card unplugged during isr */
				return IRQ_NONE;
			}

			/*
			 * should check whether all or SJA1000_MAX_IRQ
			 * interrupts have been handled: loop again to be sure.
			 */
			netdev = card->channel[i].netdev;
			if (netdev &&
			    sja1000_interrupt(irq, netdev) == IRQ_HANDLED)
				nothing_to_handle = 0;
		}

		if (nothing_to_handle)
			break;
	}

	return (irq_handled) ? IRQ_HANDLED : IRQ_NONE;
}