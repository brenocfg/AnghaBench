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
struct serio {int dummy; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IOMD_KARTRX ; 
 int /*<<< orphan*/  IOMD_KCTRL ; 
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int iomd_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_interrupt (struct serio*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t rpckbd_rx(int irq, void *dev_id)
{
	struct serio *port = dev_id;
	unsigned int byte;
	int handled = IRQ_NONE;

	while (iomd_readb(IOMD_KCTRL) & (1 << 5)) {
		byte = iomd_readb(IOMD_KARTRX);

		serio_interrupt(port, byte, 0);
		handled = IRQ_HANDLED;
	}
	return handled;
}