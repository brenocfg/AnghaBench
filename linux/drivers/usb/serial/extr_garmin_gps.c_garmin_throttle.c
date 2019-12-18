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
struct usb_serial_port {int dummy; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;
struct garmin_data {int flags; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int FLAGS_QUEUING ; 
 int FLAGS_THROTTLED ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct garmin_data* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static void garmin_throttle(struct tty_struct *tty)
{
	struct usb_serial_port *port = tty->driver_data;
	struct garmin_data *garmin_data_p = usb_get_serial_port_data(port);

	/* set flag, data received will be put into a queue
	   for later processing */
	spin_lock_irq(&garmin_data_p->lock);
	garmin_data_p->flags |= FLAGS_QUEUING|FLAGS_THROTTLED;
	spin_unlock_irq(&garmin_data_p->lock);
}