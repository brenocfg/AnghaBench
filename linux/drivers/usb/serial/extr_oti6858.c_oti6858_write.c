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
struct tty_struct {int dummy; } ;

/* Variables and functions */
 int kfifo_in_locked (int /*<<< orphan*/ *,unsigned char const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int oti6858_write(struct tty_struct *tty, struct usb_serial_port *port,
			const unsigned char *buf, int count)
{
	if (!count)
		return count;

	count = kfifo_in_locked(&port->write_fifo, buf, count, &port->lock);

	return count;
}