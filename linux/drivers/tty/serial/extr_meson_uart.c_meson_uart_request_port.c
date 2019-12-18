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
struct uart_port {int /*<<< orphan*/  membase; int /*<<< orphan*/  mapsize; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meson_uart_request_port(struct uart_port *port)
{
	if (!devm_request_mem_region(port->dev, port->mapbase, port->mapsize,
				     dev_name(port->dev))) {
		dev_err(port->dev, "Memory region busy\n");
		return -EBUSY;
	}

	port->membase = devm_ioremap_nocache(port->dev, port->mapbase,
					     port->mapsize);
	if (!port->membase)
		return -ENOMEM;

	return 0;
}