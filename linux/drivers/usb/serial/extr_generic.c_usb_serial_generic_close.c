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
struct usb_serial_port {int /*<<< orphan*/ * read_urbs; scalar_t__ bulk_in_size; int /*<<< orphan*/  lock; int /*<<< orphan*/  write_fifo; int /*<<< orphan*/ * write_urbs; scalar_t__ bulk_out_size; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_reset_out (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

void usb_serial_generic_close(struct usb_serial_port *port)
{
	unsigned long flags;
	int i;

	if (port->bulk_out_size) {
		for (i = 0; i < ARRAY_SIZE(port->write_urbs); ++i)
			usb_kill_urb(port->write_urbs[i]);

		spin_lock_irqsave(&port->lock, flags);
		kfifo_reset_out(&port->write_fifo);
		spin_unlock_irqrestore(&port->lock, flags);
	}
	if (port->bulk_in_size) {
		for (i = 0; i < ARRAY_SIZE(port->read_urbs); ++i)
			usb_kill_urb(port->read_urbs[i]);
	}
}