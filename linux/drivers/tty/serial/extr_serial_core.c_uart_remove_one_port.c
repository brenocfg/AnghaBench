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
struct tty_port {int /*<<< orphan*/  mutex; int /*<<< orphan*/  tty; } ;
struct uart_state {int /*<<< orphan*/ * uart_port; int /*<<< orphan*/  refcount; int /*<<< orphan*/  remove_wait; struct tty_port port; } ;
struct uart_port {scalar_t__ type; int /*<<< orphan*/  name; int /*<<< orphan*/  tty_groups; TYPE_1__* ops; int /*<<< orphan*/  cons; int /*<<< orphan*/  line; int /*<<< orphan*/  flags; int /*<<< orphan*/  dev; } ;
struct uart_driver {int /*<<< orphan*/  tty_driver; struct uart_state* state; } ;
struct tty_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* release_port ) (struct uart_port*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ PORT_UNKNOWN ; 
 int /*<<< orphan*/  UPF_DEAD ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ ,char*,struct uart_port*,struct uart_port*) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  port_mutex ; 
 int /*<<< orphan*/  stub1 (struct uart_port*) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (struct tty_port*) ; 
 int /*<<< orphan*/  tty_port_unregister_device (struct tty_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_vhangup (int /*<<< orphan*/ ) ; 
 scalar_t__ uart_console (struct uart_port*) ; 
 struct uart_port* uart_port_check (struct uart_state*) ; 
 int /*<<< orphan*/  unregister_console (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int uart_remove_one_port(struct uart_driver *drv, struct uart_port *uport)
{
	struct uart_state *state = drv->state + uport->line;
	struct tty_port *port = &state->port;
	struct uart_port *uart_port;
	struct tty_struct *tty;
	int ret = 0;

	BUG_ON(in_interrupt());

	mutex_lock(&port_mutex);

	/*
	 * Mark the port "dead" - this prevents any opens from
	 * succeeding while we shut down the port.
	 */
	mutex_lock(&port->mutex);
	uart_port = uart_port_check(state);
	if (uart_port != uport)
		dev_alert(uport->dev, "Removing wrong port: %p != %p\n",
			  uart_port, uport);

	if (!uart_port) {
		mutex_unlock(&port->mutex);
		ret = -EINVAL;
		goto out;
	}
	uport->flags |= UPF_DEAD;
	mutex_unlock(&port->mutex);

	/*
	 * Remove the devices from the tty layer
	 */
	tty_port_unregister_device(port, drv->tty_driver, uport->line);

	tty = tty_port_tty_get(port);
	if (tty) {
		tty_vhangup(port->tty);
		tty_kref_put(tty);
	}

	/*
	 * If the port is used as a console, unregister it
	 */
	if (uart_console(uport))
		unregister_console(uport->cons);

	/*
	 * Free the port IO and memory resources, if any.
	 */
	if (uport->type != PORT_UNKNOWN && uport->ops->release_port)
		uport->ops->release_port(uport);
	kfree(uport->tty_groups);
	kfree(uport->name);

	/*
	 * Indicate that there isn't a port here anymore.
	 */
	uport->type = PORT_UNKNOWN;

	mutex_lock(&port->mutex);
	WARN_ON(atomic_dec_return(&state->refcount) < 0);
	wait_event(state->remove_wait, !atomic_read(&state->refcount));
	state->uart_port = NULL;
	mutex_unlock(&port->mutex);
out:
	mutex_unlock(&port_mutex);

	return ret;
}