#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int flags; size_t line; int fifosize; int /*<<< orphan*/ * ops; scalar_t__ x_char; int /*<<< orphan*/  type; TYPE_1__* dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  mapsize; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  iotype; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_3__ {scalar_t__ of_node; } ;
struct platform_device {int id; TYPE_1__ dev; } ;

/* Variables and functions */
 int AML_UART_PORT_NUM ; 
 int AML_UART_PORT_OFFSET ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  PORT_MESON ; 
 int UPF_BOOT_AUTOCONF ; 
 int UPF_LOW_LATENCY ; 
 int /*<<< orphan*/  UPIO_MEM ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,size_t) ; 
 struct uart_port* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct uart_port** meson_ports ; 
 int /*<<< orphan*/  meson_uart_driver ; 
 int /*<<< orphan*/  meson_uart_ops ; 
 int meson_uart_probe_clocks (struct platform_device*,struct uart_port*) ; 
 int meson_uart_probe_clocks_legacy (struct platform_device*,struct uart_port*) ; 
 int /*<<< orphan*/  meson_uart_release_port (struct uart_port*) ; 
 scalar_t__ meson_uart_request_port (struct uart_port*) ; 
 int /*<<< orphan*/  meson_uart_reset (struct uart_port*) ; 
 int of_alias_get_id (scalar_t__,char*) ; 
 scalar_t__ of_device_is_compatible (scalar_t__,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct uart_port*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int uart_add_one_port (int /*<<< orphan*/ *,struct uart_port*) ; 

__attribute__((used)) static int meson_uart_probe(struct platform_device *pdev)
{
	struct resource *res_mem, *res_irq;
	struct uart_port *port;
	int ret = 0;
	int id = -1;

	if (pdev->dev.of_node)
		pdev->id = of_alias_get_id(pdev->dev.of_node, "serial");

	if (pdev->id < 0) {
		for (id = AML_UART_PORT_OFFSET; id < AML_UART_PORT_NUM; id++) {
			if (!meson_ports[id]) {
				pdev->id = id;
				break;
			}
		}
	}

	if (pdev->id < 0 || pdev->id >= AML_UART_PORT_NUM)
		return -EINVAL;

	res_mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res_mem)
		return -ENODEV;

	res_irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!res_irq)
		return -ENODEV;

	if (meson_ports[pdev->id]) {
		dev_err(&pdev->dev, "port %d already allocated\n", pdev->id);
		return -EBUSY;
	}

	port = devm_kzalloc(&pdev->dev, sizeof(struct uart_port), GFP_KERNEL);
	if (!port)
		return -ENOMEM;

	/* Use legacy way until all platforms switch to new bindings */
	if (of_device_is_compatible(pdev->dev.of_node, "amlogic,meson-uart"))
		ret = meson_uart_probe_clocks_legacy(pdev, port);
	else
		ret = meson_uart_probe_clocks(pdev, port);

	if (ret)
		return ret;

	port->iotype = UPIO_MEM;
	port->mapbase = res_mem->start;
	port->mapsize = resource_size(res_mem);
	port->irq = res_irq->start;
	port->flags = UPF_BOOT_AUTOCONF | UPF_LOW_LATENCY;
	port->dev = &pdev->dev;
	port->line = pdev->id;
	port->type = PORT_MESON;
	port->x_char = 0;
	port->ops = &meson_uart_ops;
	port->fifosize = 64;

	meson_ports[pdev->id] = port;
	platform_set_drvdata(pdev, port);

	/* reset port before registering (and possibly registering console) */
	if (meson_uart_request_port(port) >= 0) {
		meson_uart_reset(port);
		meson_uart_release_port(port);
	}

	ret = uart_add_one_port(&meson_uart_driver, port);
	if (ret)
		meson_ports[pdev->id] = NULL;

	return ret;
}