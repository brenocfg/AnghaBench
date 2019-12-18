#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_6__ {scalar_t__ of_node; } ;
struct platform_device {size_t id; TYPE_2__ dev; } ;
struct TYPE_5__ {size_t line; int irq; scalar_t__ uartclk; int flags; int fifosize; int /*<<< orphan*/ * ops; scalar_t__ x_char; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  iotype; int /*<<< orphan*/  type; TYPE_2__* dev; } ;
struct owl_uart_port {TYPE_1__ port; int /*<<< orphan*/  clk; } ;
struct owl_uart_info {int tx_fifosize; } ;
struct of_device_id {struct owl_uart_info* data; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 size_t OWL_UART_PORT_NUM ; 
 int /*<<< orphan*/  PORT_OWL ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int UPF_BOOT_AUTOCONF ; 
 int UPF_IOREMAP ; 
 int UPF_LOW_LATENCY ; 
 int /*<<< orphan*/  UPIO_MEM ; 
 scalar_t__ clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 struct owl_uart_port* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 size_t of_alias_get_id (scalar_t__,char*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  owl_uart_driver ; 
 int /*<<< orphan*/  owl_uart_dt_matches ; 
 int /*<<< orphan*/  owl_uart_ops ; 
 struct owl_uart_port** owl_uart_ports ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct owl_uart_port*) ; 
 int uart_add_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int owl_uart_probe(struct platform_device *pdev)
{
	const struct of_device_id *match;
	const struct owl_uart_info *info = NULL;
	struct resource *res_mem;
	struct owl_uart_port *owl_port;
	int ret, irq;

	if (pdev->dev.of_node) {
		pdev->id = of_alias_get_id(pdev->dev.of_node, "serial");
		match = of_match_node(owl_uart_dt_matches, pdev->dev.of_node);
		if (match)
			info = match->data;
	}

	if (pdev->id < 0 || pdev->id >= OWL_UART_PORT_NUM) {
		dev_err(&pdev->dev, "id %d out of range\n", pdev->id);
		return -EINVAL;
	}

	res_mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res_mem) {
		dev_err(&pdev->dev, "could not get mem\n");
		return -ENODEV;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	if (owl_uart_ports[pdev->id]) {
		dev_err(&pdev->dev, "port %d already allocated\n", pdev->id);
		return -EBUSY;
	}

	owl_port = devm_kzalloc(&pdev->dev, sizeof(*owl_port), GFP_KERNEL);
	if (!owl_port)
		return -ENOMEM;

	owl_port->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(owl_port->clk)) {
		dev_err(&pdev->dev, "could not get clk\n");
		return PTR_ERR(owl_port->clk);
	}

	owl_port->port.dev = &pdev->dev;
	owl_port->port.line = pdev->id;
	owl_port->port.type = PORT_OWL;
	owl_port->port.iotype = UPIO_MEM;
	owl_port->port.mapbase = res_mem->start;
	owl_port->port.irq = irq;
	owl_port->port.uartclk = clk_get_rate(owl_port->clk);
	if (owl_port->port.uartclk == 0) {
		dev_err(&pdev->dev, "clock rate is zero\n");
		return -EINVAL;
	}
	owl_port->port.flags = UPF_BOOT_AUTOCONF | UPF_IOREMAP | UPF_LOW_LATENCY;
	owl_port->port.x_char = 0;
	owl_port->port.fifosize = (info) ? info->tx_fifosize : 16;
	owl_port->port.ops = &owl_uart_ops;

	owl_uart_ports[pdev->id] = owl_port;
	platform_set_drvdata(pdev, owl_port);

	ret = uart_add_one_port(&owl_uart_driver, &owl_port->port);
	if (ret)
		owl_uart_ports[pdev->id] = NULL;

	return ret;
}