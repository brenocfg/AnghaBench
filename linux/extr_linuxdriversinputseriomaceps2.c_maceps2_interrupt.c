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
struct serio {scalar_t__ port_data; } ;
struct maceps2_data {struct mace_ps2port* port; } ;
struct mace_ps2port {int status; unsigned long rx; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int PS2_STATUS_RX_FULL ; 
 int /*<<< orphan*/  serio_interrupt (struct serio*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t maceps2_interrupt(int irq, void *dev_id)
{
	struct serio *dev = dev_id;
	struct mace_ps2port *port = ((struct maceps2_data *)dev->port_data)->port;
	unsigned long byte;

	if (port->status & PS2_STATUS_RX_FULL) {
		byte = port->rx;
		serio_interrupt(dev, byte & 0xff, 0);
        }

	return IRQ_HANDLED;
}