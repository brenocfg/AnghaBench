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
struct gserial {int /*<<< orphan*/  in; int /*<<< orphan*/  out; struct gs_port* ioport; int /*<<< orphan*/  port_line_coding; } ;
struct TYPE_2__ {scalar_t__ count; scalar_t__ tty; } ;
struct gs_port {int /*<<< orphan*/  port_lock; scalar_t__ write_started; scalar_t__ write_allocated; scalar_t__ read_started; scalar_t__ read_allocated; int /*<<< orphan*/  write_pool; int /*<<< orphan*/  read_queue; int /*<<< orphan*/  read_pool; int /*<<< orphan*/  port_write_buf; scalar_t__ openclose; TYPE_1__ port; int /*<<< orphan*/  drain_wait; int /*<<< orphan*/ * port_usb; int /*<<< orphan*/  port_line_coding; } ;

/* Variables and functions */
 int /*<<< orphan*/  gs_console_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_free_requests (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_hangup (scalar_t__) ; 
 int /*<<< orphan*/  usb_ep_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void gserial_disconnect(struct gserial *gser)
{
	struct gs_port	*port = gser->ioport;
	unsigned long	flags;

	if (!port)
		return;

	/* tell the TTY glue not to do I/O here any more */
	spin_lock_irqsave(&port->port_lock, flags);

	/* REVISIT as above: how best to track this? */
	port->port_line_coding = gser->port_line_coding;

	port->port_usb = NULL;
	gser->ioport = NULL;
	if (port->port.count > 0 || port->openclose) {
		wake_up_interruptible(&port->drain_wait);
		if (port->port.tty)
			tty_hangup(port->port.tty);
	}
	spin_unlock_irqrestore(&port->port_lock, flags);

	/* disable endpoints, aborting down any active I/O */
	usb_ep_disable(gser->out);
	usb_ep_disable(gser->in);

	/* finally, free any unused/unusable I/O buffers */
	spin_lock_irqsave(&port->port_lock, flags);
	if (port->port.count == 0 && !port->openclose)
		kfifo_free(&port->port_write_buf);
	gs_free_requests(gser->out, &port->read_pool, NULL);
	gs_free_requests(gser->out, &port->read_queue, NULL);
	gs_free_requests(gser->in, &port->write_pool, NULL);

	port->read_allocated = port->read_started =
		port->write_allocated = port->write_started = 0;

	gs_console_disconnect(gser->in);
	spin_unlock_irqrestore(&port->port_lock, flags);
}