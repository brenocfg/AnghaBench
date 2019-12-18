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
struct ps2if {int /*<<< orphan*/  io; int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_interrupt (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t altera_ps2_rxint(int irq, void *dev_id)
{
	struct ps2if *ps2if = dev_id;
	unsigned int status;
	irqreturn_t handled = IRQ_NONE;

	while ((status = readl(ps2if->base)) & 0xffff0000) {
		serio_interrupt(ps2if->io, status & 0xff, 0);
		handled = IRQ_HANDLED;
	}

	return handled;
}