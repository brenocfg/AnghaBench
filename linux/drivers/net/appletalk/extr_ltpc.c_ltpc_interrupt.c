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
struct net_device {scalar_t__ base_addr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  idle (struct net_device*) ; 
 int /*<<< orphan*/  inb_p (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static irqreturn_t
ltpc_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;

	if (dev==NULL) {
		printk("ltpc_interrupt: unknown device.\n");
		return IRQ_NONE;
	}

	inb_p(dev->base_addr+6);  /* disable further interrupts from board */

	idle(dev); /* handle whatever is coming in */
 
	/* idle re-enables interrupts from board */ 

	return IRQ_HANDLED;
}