#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int nr; } ;

/* Variables and functions */
 TYPE_1__ siu_uart_driver ; 
 struct uart_port* siu_uart_ports ; 
 int /*<<< orphan*/  uart_remove_one_port (TYPE_1__*,struct uart_port*) ; 
 int /*<<< orphan*/  uart_unregister_driver (TYPE_1__*) ; 

__attribute__((used)) static int siu_remove(struct platform_device *dev)
{
	struct uart_port *port;
	int i;

	for (i = 0; i < siu_uart_driver.nr; i++) {
		port = &siu_uart_ports[i];
		if (port->dev == &dev->dev) {
			uart_remove_one_port(&siu_uart_driver, port);
			port->dev = NULL;
		}
	}

	uart_unregister_driver(&siu_uart_driver);

	return 0;
}