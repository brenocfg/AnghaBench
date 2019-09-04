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
struct serio {scalar_t__ port_data; } ;
struct maceps2_data {int /*<<< orphan*/  irq; TYPE_1__* port; } ;
struct TYPE_2__ {int control; } ;

/* Variables and functions */
 int PS2_CONTROL_RESET ; 
 int PS2_CONTROL_TX_CLOCK_DISABLE ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct serio*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void maceps2_close(struct serio *dev)
{
	struct maceps2_data *data = (struct maceps2_data *)dev->port_data;

	data->port->control = PS2_CONTROL_TX_CLOCK_DISABLE | PS2_CONTROL_RESET;
	udelay(100);
	free_irq(data->irq, dev);
}