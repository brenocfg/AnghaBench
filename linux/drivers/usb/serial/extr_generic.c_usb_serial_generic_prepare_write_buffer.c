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
struct usb_serial_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  write_fifo; } ;

/* Variables and functions */
 int kfifo_out_locked (int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/ *) ; 

int usb_serial_generic_prepare_write_buffer(struct usb_serial_port *port,
						void *dest, size_t size)
{
	return kfifo_out_locked(&port->write_fifo, dest, size, &port->lock);
}