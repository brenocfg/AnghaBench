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
struct TYPE_2__ {int /*<<< orphan*/  tty; } ;
struct serial_state {TYPE_1__ tport; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  receive_chars (struct serial_state*) ; 

__attribute__((used)) static irqreturn_t ser_rx_int(int irq, void *dev_id)
{
	struct serial_state *info = dev_id;

#ifdef SERIAL_DEBUG_INTR
	printk("ser_rx_int...");
#endif

	if (!info->tport.tty)
		return IRQ_NONE;

	receive_chars(info);
#ifdef SERIAL_DEBUG_INTR
	printk("end.\n");
#endif
	return IRQ_HANDLED;
}