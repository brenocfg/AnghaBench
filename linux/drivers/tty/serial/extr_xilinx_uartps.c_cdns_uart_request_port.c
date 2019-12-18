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
struct uart_port {int /*<<< orphan*/  mapbase; int /*<<< orphan*/  dev; int /*<<< orphan*/  membase; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNS_UART_NAME ; 
 int /*<<< orphan*/  CDNS_UART_REGISTER_SPACE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdns_uart_request_port(struct uart_port *port)
{
	if (!request_mem_region(port->mapbase, CDNS_UART_REGISTER_SPACE,
					 CDNS_UART_NAME)) {
		return -ENOMEM;
	}

	port->membase = ioremap(port->mapbase, CDNS_UART_REGISTER_SPACE);
	if (!port->membase) {
		dev_err(port->dev, "Unable to map registers\n");
		release_mem_region(port->mapbase, CDNS_UART_REGISTER_SPACE);
		return -ENOMEM;
	}
	return 0;
}