#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int /*<<< orphan*/ * dev; int /*<<< orphan*/ * ops; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int nr; } ;

/* Variables and functions */
 int ENODEV ; 
 int siu_init_ports (struct platform_device*) ; 
 TYPE_1__ siu_uart_driver ; 
 int /*<<< orphan*/  siu_uart_ops ; 
 struct uart_port* siu_uart_ports ; 
 int uart_add_one_port (TYPE_1__*,struct uart_port*) ; 
 int uart_register_driver (TYPE_1__*) ; 
 int /*<<< orphan*/  uart_unregister_driver (TYPE_1__*) ; 

__attribute__((used)) static int siu_probe(struct platform_device *dev)
{
	struct uart_port *port;
	int num, i, retval;

	num = siu_init_ports(dev);
	if (num <= 0)
		return -ENODEV;

	siu_uart_driver.nr = num;
	retval = uart_register_driver(&siu_uart_driver);
	if (retval)
		return retval;

	for (i = 0; i < num; i++) {
		port = &siu_uart_ports[i];
		port->ops = &siu_uart_ops;
		port->dev = &dev->dev;

		retval = uart_add_one_port(&siu_uart_driver, port);
		if (retval < 0) {
			port->dev = NULL;
			break;
		}
	}

	if (i == 0 && retval < 0) {
		uart_unregister_driver(&siu_uart_driver);
		return retval;
	}

	return 0;
}