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
struct serio {struct i8042_port* port_data; } ;
struct i8042_port {int exists; int /*<<< orphan*/ * serio; } ;

/* Variables and functions */
 int /*<<< orphan*/  I8042_AUX_IRQ ; 
 int /*<<< orphan*/  I8042_KBD_IRQ ; 
 int /*<<< orphan*/  i8042_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i8042_stop(struct serio *serio)
{
	struct i8042_port *port = serio->port_data;

	spin_lock_irq(&i8042_lock);
	port->exists = false;
	port->serio = NULL;
	spin_unlock_irq(&i8042_lock);

	/*
	 * We need to make sure that interrupt handler finishes using
	 * our serio port before we return from this function.
	 * We synchronize with both AUX and KBD IRQs because there is
	 * a (very unlikely) chance that AUX IRQ is raised for KBD port
	 * and vice versa.
	 */
	synchronize_irq(I8042_AUX_IRQ);
	synchronize_irq(I8042_KBD_IRQ);
}