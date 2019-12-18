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
 unsigned char ir_baud ; 
 unsigned char ir_xbof ; 
 int kfifo_out_locked (int /*<<< orphan*/ *,unsigned char*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ir_prepare_write_buffer(struct usb_serial_port *port,
						void *dest, size_t size)
{
	unsigned char *buf = dest;
	int count;

	/*
	 * The first byte of the packet we send to the device contains an
	 * inbound header which indicates an additional number of BOFs and
	 * a baud rate change.
	 *
	 * See section 5.4.2.2 of the USB IrDA spec.
	 */
	*buf = ir_xbof | ir_baud;

	count = kfifo_out_locked(&port->write_fifo, buf + 1, size - 1,
								&port->lock);
	return count + 1;
}