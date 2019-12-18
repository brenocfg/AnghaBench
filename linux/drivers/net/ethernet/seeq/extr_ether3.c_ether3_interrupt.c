#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
typedef  unsigned int irqreturn_t ;
struct TYPE_3__ {int command; } ;
struct TYPE_4__ {TYPE_1__ regs; } ;

/* Variables and functions */
 int CMD_ACKINTRX ; 
 int CMD_ACKINTTX ; 
 int DEBUG_INT ; 
 unsigned int IRQ_HANDLED ; 
 unsigned int IRQ_NONE ; 
 int /*<<< orphan*/  REG_COMMAND ; 
 int /*<<< orphan*/  REG_STATUS ; 
 unsigned int STAT_INTRX ; 
 unsigned int STAT_INTTX ; 
 unsigned int ether3_inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether3_outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether3_rx (struct net_device*,int) ; 
 int /*<<< orphan*/  ether3_tx (struct net_device*) ; 
 int net_debug ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 TYPE_2__* priv (struct net_device*) ; 

__attribute__((used)) static irqreturn_t
ether3_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *)dev_id;
	unsigned int status, handled = IRQ_NONE;

#if NET_DEBUG > 1
	if(net_debug & DEBUG_INT)
		printk("eth3irq: %d ", irq);
#endif

	status = ether3_inw(REG_STATUS);

	if (status & STAT_INTRX) {
		ether3_outw(CMD_ACKINTRX | priv(dev)->regs.command, REG_COMMAND);
		ether3_rx(dev, 12);
		handled = IRQ_HANDLED;
	}

	if (status & STAT_INTTX) {
		ether3_outw(CMD_ACKINTTX | priv(dev)->regs.command, REG_COMMAND);
		ether3_tx(dev);
		handled = IRQ_HANDLED;
	}

#if NET_DEBUG > 1
	if(net_debug & DEBUG_INT)
		printk("done\n");
#endif
	return handled;
}