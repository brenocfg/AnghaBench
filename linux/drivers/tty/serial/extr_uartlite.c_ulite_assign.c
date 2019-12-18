#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct uartlite_data {int dummy; } ;
struct uart_port {scalar_t__ mapbase; int fifosize; int regshift; int iobase; int irq; int line; struct uartlite_data* private_data; int /*<<< orphan*/  type; struct device* dev; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * membase; int /*<<< orphan*/  iotype; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;
struct TYPE_5__ {TYPE_1__* cons; } ;
struct TYPE_4__ {int index; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  PORT_UNKNOWN ; 
 int /*<<< orphan*/  ULITE_NAME ; 
 int ULITE_NR_UARTS ; 
 int /*<<< orphan*/  UPF_BOOT_AUTOCONF ; 
 int /*<<< orphan*/  UPIO_MEM ; 
 struct uart_port* console_port ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct uart_port*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int uart_add_one_port (TYPE_2__*,struct uart_port*) ; 
 int /*<<< orphan*/  ulite_ops ; 
 struct uart_port* ulite_ports ; 
 TYPE_2__ ulite_uart_driver ; 

__attribute__((used)) static int ulite_assign(struct device *dev, int id, u32 base, int irq,
			struct uartlite_data *pdata)
{
	struct uart_port *port;
	int rc;

	/* if id = -1; then scan for a free id and use that */
	if (id < 0) {
		for (id = 0; id < ULITE_NR_UARTS; id++)
			if (ulite_ports[id].mapbase == 0)
				break;
	}
	if (id < 0 || id >= ULITE_NR_UARTS) {
		dev_err(dev, "%s%i too large\n", ULITE_NAME, id);
		return -EINVAL;
	}

	if ((ulite_ports[id].mapbase) && (ulite_ports[id].mapbase != base)) {
		dev_err(dev, "cannot assign to %s%i; it is already in use\n",
			ULITE_NAME, id);
		return -EBUSY;
	}

	port = &ulite_ports[id];

	spin_lock_init(&port->lock);
	port->fifosize = 16;
	port->regshift = 2;
	port->iotype = UPIO_MEM;
	port->iobase = 1; /* mark port in use */
	port->mapbase = base;
	port->membase = NULL;
	port->ops = &ulite_ops;
	port->irq = irq;
	port->flags = UPF_BOOT_AUTOCONF;
	port->dev = dev;
	port->type = PORT_UNKNOWN;
	port->line = id;
	port->private_data = pdata;

	dev_set_drvdata(dev, port);

#ifdef CONFIG_SERIAL_UARTLITE_CONSOLE
	/*
	 * If console hasn't been found yet try to assign this port
	 * because it is required to be assigned for console setup function.
	 * If register_console() don't assign value, then console_port pointer
	 * is cleanup.
	 */
	if (ulite_uart_driver.cons->index == -1)
		console_port = port;
#endif

	/* Register the port */
	rc = uart_add_one_port(&ulite_uart_driver, port);
	if (rc) {
		dev_err(dev, "uart_add_one_port() failed; err=%i\n", rc);
		port->mapbase = 0;
		dev_set_drvdata(dev, NULL);
		return rc;
	}

#ifdef CONFIG_SERIAL_UARTLITE_CONSOLE
	/* This is not port which is used for console that's why clean it up */
	if (ulite_uart_driver.cons->index == -1)
		console_port = NULL;
#endif

	return 0;
}