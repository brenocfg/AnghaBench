#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tty_port {int /*<<< orphan*/  mutex; scalar_t__ console; } ;
struct uart_state {int /*<<< orphan*/  pm_state; struct uart_port* uart_port; int /*<<< orphan*/  remove_wait; int /*<<< orphan*/  refcount; struct tty_port port; } ;
struct uart_port {int /*<<< orphan*/  flags; scalar_t__ line; TYPE_3__* dev; int /*<<< orphan*/ ** tty_groups; int /*<<< orphan*/ * attr_group; TYPE_1__* cons; int /*<<< orphan*/  lock; int /*<<< orphan*/  name; scalar_t__ minor; struct uart_state* state; } ;
struct uart_driver {TYPE_2__* tty_driver; int /*<<< orphan*/  dev_name; TYPE_1__* cons; struct uart_state* state; scalar_t__ nr; } ;
struct device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_6__ {scalar_t__ name_base; scalar_t__ minor_start; } ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int CON_ENABLED ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct device*) ; 
 int /*<<< orphan*/  UART_PM_STATE_UNDEFINED ; 
 int /*<<< orphan*/  UPF_DEAD ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (struct device*,int) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ ** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_console_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  port_lock_key ; 
 int /*<<< orphan*/  port_mutex ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_dev_attr_group ; 
 struct device* tty_port_register_device_attr_serdev (struct tty_port*,TYPE_2__*,scalar_t__,TYPE_3__*,struct tty_port*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uart_configure_port (struct uart_driver*,struct uart_state*,struct uart_port*) ; 
 scalar_t__ uart_console (struct uart_port*) ; 

int uart_add_one_port(struct uart_driver *drv, struct uart_port *uport)
{
	struct uart_state *state;
	struct tty_port *port;
	int ret = 0;
	struct device *tty_dev;
	int num_groups;

	BUG_ON(in_interrupt());

	if (uport->line >= drv->nr)
		return -EINVAL;

	state = drv->state + uport->line;
	port = &state->port;

	mutex_lock(&port_mutex);
	mutex_lock(&port->mutex);
	if (state->uart_port) {
		ret = -EINVAL;
		goto out;
	}

	/* Link the port to the driver state table and vice versa */
	atomic_set(&state->refcount, 1);
	init_waitqueue_head(&state->remove_wait);
	state->uart_port = uport;
	uport->state = state;

	state->pm_state = UART_PM_STATE_UNDEFINED;
	uport->cons = drv->cons;
	uport->minor = drv->tty_driver->minor_start + uport->line;
	uport->name = kasprintf(GFP_KERNEL, "%s%d", drv->dev_name,
				drv->tty_driver->name_base + uport->line);
	if (!uport->name) {
		ret = -ENOMEM;
		goto out;
	}

	/*
	 * If this port is a console, then the spinlock is already
	 * initialised.
	 */
	if (!(uart_console(uport) && (uport->cons->flags & CON_ENABLED))) {
		spin_lock_init(&uport->lock);
		lockdep_set_class(&uport->lock, &port_lock_key);
	}
	if (uport->cons && uport->dev)
		of_console_check(uport->dev->of_node, uport->cons->name, uport->line);

	uart_configure_port(drv, state, uport);

	port->console = uart_console(uport);

	num_groups = 2;
	if (uport->attr_group)
		num_groups++;

	uport->tty_groups = kcalloc(num_groups, sizeof(*uport->tty_groups),
				    GFP_KERNEL);
	if (!uport->tty_groups) {
		ret = -ENOMEM;
		goto out;
	}
	uport->tty_groups[0] = &tty_dev_attr_group;
	if (uport->attr_group)
		uport->tty_groups[1] = uport->attr_group;

	/*
	 * Register the port whether it's detected or not.  This allows
	 * setserial to be used to alter this port's parameters.
	 */
	tty_dev = tty_port_register_device_attr_serdev(port, drv->tty_driver,
			uport->line, uport->dev, port, uport->tty_groups);
	if (!IS_ERR(tty_dev)) {
		device_set_wakeup_capable(tty_dev, 1);
	} else {
		dev_err(uport->dev, "Cannot register tty device on line %d\n",
		       uport->line);
	}

	/*
	 * Ensure UPF_DEAD is not set.
	 */
	uport->flags &= ~UPF_DEAD;

 out:
	mutex_unlock(&port->mutex);
	mutex_unlock(&port_mutex);

	return ret;
}