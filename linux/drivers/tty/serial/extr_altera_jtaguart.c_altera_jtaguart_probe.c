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
struct uart_port {int line; int /*<<< orphan*/ * dev; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; int /*<<< orphan*/  iotype; int /*<<< orphan*/  type; int /*<<< orphan*/  membase; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  irq; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int id; int /*<<< orphan*/  dev; } ;
struct altera_jtaguart_platform_uart {int /*<<< orphan*/  irq; int /*<<< orphan*/  mapbase; } ;
struct TYPE_2__ {struct uart_port port; } ;

/* Variables and functions */
 int ALTERA_JTAGUART_MAXPORTS ; 
 int /*<<< orphan*/  ALTERA_JTAGUART_SIZE ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  PORT_ALTERA_JTAGUART ; 
 int /*<<< orphan*/  SERIAL_IO_MEM ; 
 int /*<<< orphan*/  UPF_BOOT_AUTOCONF ; 
 int /*<<< orphan*/  altera_jtaguart_driver ; 
 int /*<<< orphan*/  altera_jtaguart_ops ; 
 TYPE_1__* altera_jtaguart_ports ; 
 struct altera_jtaguart_platform_uart* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_add_one_port (int /*<<< orphan*/ *,struct uart_port*) ; 

__attribute__((used)) static int altera_jtaguart_probe(struct platform_device *pdev)
{
	struct altera_jtaguart_platform_uart *platp =
			dev_get_platdata(&pdev->dev);
	struct uart_port *port;
	struct resource *res_irq, *res_mem;
	int i = pdev->id;

	/* -1 emphasizes that the platform must have one port, no .N suffix */
	if (i == -1)
		i = 0;

	if (i >= ALTERA_JTAGUART_MAXPORTS)
		return -EINVAL;

	port = &altera_jtaguart_ports[i].port;

	res_mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res_mem)
		port->mapbase = res_mem->start;
	else if (platp)
		port->mapbase = platp->mapbase;
	else
		return -ENODEV;

	res_irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (res_irq)
		port->irq = res_irq->start;
	else if (platp)
		port->irq = platp->irq;
	else
		return -ENODEV;

	port->membase = ioremap(port->mapbase, ALTERA_JTAGUART_SIZE);
	if (!port->membase)
		return -ENOMEM;

	port->line = i;
	port->type = PORT_ALTERA_JTAGUART;
	port->iotype = SERIAL_IO_MEM;
	port->ops = &altera_jtaguart_ops;
	port->flags = UPF_BOOT_AUTOCONF;
	port->dev = &pdev->dev;

	uart_add_one_port(&altera_jtaguart_driver, port);

	return 0;
}