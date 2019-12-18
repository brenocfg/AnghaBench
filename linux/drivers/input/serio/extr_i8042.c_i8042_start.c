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
struct serio {int /*<<< orphan*/  dev; struct i8042_port* port_data; } ;
struct i8042_port {int exists; } ;
struct TYPE_2__ {struct serio* serio; } ;

/* Variables and functions */
 size_t I8042_KBD_PORT_NO ; 
 int /*<<< orphan*/  device_set_wakeup_capable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_set_wakeup_enable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i8042_lock ; 
 TYPE_1__* i8042_ports ; 
 scalar_t__ pm_suspend_default_s2idle () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i8042_start(struct serio *serio)
{
	struct i8042_port *port = serio->port_data;

	device_set_wakeup_capable(&serio->dev, true);

	/*
	 * On platforms using suspend-to-idle, allow the keyboard to
	 * wake up the system from sleep by enabling keyboard wakeups
	 * by default.  This is consistent with keyboard wakeup
	 * behavior on many platforms using suspend-to-RAM (ACPI S3)
	 * by default.
	 */
	if (pm_suspend_default_s2idle() &&
	    serio == i8042_ports[I8042_KBD_PORT_NO].serio) {
		device_set_wakeup_enable(&serio->dev, true);
	}

	spin_lock_irq(&i8042_lock);
	port->exists = true;
	spin_unlock_irq(&i8042_lock);

	return 0;
}