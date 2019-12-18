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
struct tty_port {int /*<<< orphan*/ * ops; } ;
struct uart_state {struct tty_port port; } ;
struct uart_driver {int nr; struct uart_state* state; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  driver_name; struct tty_driver* tty_driver; } ;
struct TYPE_2__ {int c_cflag; int c_ispeed; int c_ospeed; } ;
struct tty_driver {int flags; struct uart_driver* driver_state; TYPE_1__ init_termios; int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; int /*<<< orphan*/  minor_start; int /*<<< orphan*/  major; int /*<<< orphan*/  name; int /*<<< orphan*/  driver_name; } ;

/* Variables and functions */
 int B9600 ; 
 int /*<<< orphan*/  BUG_ON (struct uart_state*) ; 
 int CLOCAL ; 
 int CREAD ; 
 int CS8 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HUPCL ; 
 int /*<<< orphan*/  SERIAL_TYPE_NORMAL ; 
 int TTY_DRIVER_DYNAMIC_DEV ; 
 int TTY_DRIVER_REAL_RAW ; 
 int /*<<< orphan*/  TTY_DRIVER_TYPE_SERIAL ; 
 struct tty_driver* alloc_tty_driver (int) ; 
 struct uart_state* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct uart_state*) ; 
 int /*<<< orphan*/  put_tty_driver (struct tty_driver*) ; 
 int /*<<< orphan*/  tty_port_destroy (struct tty_port*) ; 
 int /*<<< orphan*/  tty_port_init (struct tty_port*) ; 
 int tty_register_driver (struct tty_driver*) ; 
 int /*<<< orphan*/  tty_set_operations (struct tty_driver*,int /*<<< orphan*/ *) ; 
 TYPE_1__ tty_std_termios ; 
 int /*<<< orphan*/  uart_ops ; 
 int /*<<< orphan*/  uart_port_ops ; 

int uart_register_driver(struct uart_driver *drv)
{
	struct tty_driver *normal;
	int i, retval = -ENOMEM;

	BUG_ON(drv->state);

	/*
	 * Maybe we should be using a slab cache for this, especially if
	 * we have a large number of ports to handle.
	 */
	drv->state = kcalloc(drv->nr, sizeof(struct uart_state), GFP_KERNEL);
	if (!drv->state)
		goto out;

	normal = alloc_tty_driver(drv->nr);
	if (!normal)
		goto out_kfree;

	drv->tty_driver = normal;

	normal->driver_name	= drv->driver_name;
	normal->name		= drv->dev_name;
	normal->major		= drv->major;
	normal->minor_start	= drv->minor;
	normal->type		= TTY_DRIVER_TYPE_SERIAL;
	normal->subtype		= SERIAL_TYPE_NORMAL;
	normal->init_termios	= tty_std_termios;
	normal->init_termios.c_cflag = B9600 | CS8 | CREAD | HUPCL | CLOCAL;
	normal->init_termios.c_ispeed = normal->init_termios.c_ospeed = 9600;
	normal->flags		= TTY_DRIVER_REAL_RAW | TTY_DRIVER_DYNAMIC_DEV;
	normal->driver_state    = drv;
	tty_set_operations(normal, &uart_ops);

	/*
	 * Initialise the UART state(s).
	 */
	for (i = 0; i < drv->nr; i++) {
		struct uart_state *state = drv->state + i;
		struct tty_port *port = &state->port;

		tty_port_init(port);
		port->ops = &uart_port_ops;
	}

	retval = tty_register_driver(normal);
	if (retval >= 0)
		return retval;

	for (i = 0; i < drv->nr; i++)
		tty_port_destroy(&drv->state[i].port);
	put_tty_driver(normal);
out_kfree:
	kfree(drv->state);
out:
	return retval;
}