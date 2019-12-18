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
struct uart_port {int /*<<< orphan*/ * membase; int /*<<< orphan*/  mapbase; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct men_z135_port {struct resource* mem; struct mcb_device* mdev; } ;
struct mcb_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct resource*) ; 
 int PTR_ERR (struct resource*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcb_release_mem (struct resource*) ; 
 struct resource* mcb_request_mem (struct mcb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 struct men_z135_port* to_men_z135 (struct uart_port*) ; 

__attribute__((used)) static int men_z135_request_port(struct uart_port *port)
{
	struct men_z135_port *uart = to_men_z135(port);
	struct mcb_device *mdev = uart->mdev;
	struct resource *mem;

	mem = mcb_request_mem(uart->mdev, dev_name(&mdev->dev));
	if (IS_ERR(mem))
		return PTR_ERR(mem);

	port->mapbase = mem->start;
	uart->mem = mem;

	port->membase = ioremap(mem->start, resource_size(mem));
	if (port->membase == NULL) {
		mcb_release_mem(mem);
		return -ENOMEM;
	}

	return 0;
}