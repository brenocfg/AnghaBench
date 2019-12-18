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
struct tty_struct {struct gs_port* driver_data; } ;
struct gserial {int /*<<< orphan*/  (* disconnect ) (struct gserial*) ;} ;
struct TYPE_2__ {int count; int /*<<< orphan*/ * tty; } ;
struct gs_port {int openclose; int /*<<< orphan*/  port_lock; int /*<<< orphan*/  close_wait; int /*<<< orphan*/  port_num; TYPE_1__ port; int /*<<< orphan*/  port_write_buf; struct gserial* port_usb; int /*<<< orphan*/  drain_wait; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int GS_CLOSE_TIMEOUT ; 
 int HZ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  gs_writes_finished (struct gs_port*) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 scalar_t__ kfifo_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,struct tty_struct*,struct file*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct gserial*) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gs_close(struct tty_struct *tty, struct file *file)
{
	struct gs_port *port = tty->driver_data;
	struct gserial	*gser;

	spin_lock_irq(&port->port_lock);

	if (port->port.count != 1) {
		if (port->port.count == 0)
			WARN_ON(1);
		else
			--port->port.count;
		goto exit;
	}

	pr_debug("gs_close: ttyGS%d (%p,%p) ...\n", port->port_num, tty, file);

	/* mark port as closing but in use; we can drop port lock
	 * and sleep if necessary
	 */
	port->openclose = true;
	port->port.count = 0;

	gser = port->port_usb;
	if (gser && gser->disconnect)
		gser->disconnect(gser);

	/* wait for circular write buffer to drain, disconnect, or at
	 * most GS_CLOSE_TIMEOUT seconds; then discard the rest
	 */
	if (kfifo_len(&port->port_write_buf) > 0 && gser) {
		spin_unlock_irq(&port->port_lock);
		wait_event_interruptible_timeout(port->drain_wait,
					gs_writes_finished(port),
					GS_CLOSE_TIMEOUT * HZ);
		spin_lock_irq(&port->port_lock);
		gser = port->port_usb;
	}

	/* Iff we're disconnected, there can be no I/O in flight so it's
	 * ok to free the circular buffer; else just scrub it.  And don't
	 * let the push tasklet fire again until we're re-opened.
	 */
	if (gser == NULL)
		kfifo_free(&port->port_write_buf);
	else
		kfifo_reset(&port->port_write_buf);

	port->port.tty = NULL;

	port->openclose = false;

	pr_debug("gs_close: ttyGS%d (%p,%p) done!\n",
			port->port_num, tty, file);

	wake_up(&port->close_wait);
exit:
	spin_unlock_irq(&port->port_lock);
}