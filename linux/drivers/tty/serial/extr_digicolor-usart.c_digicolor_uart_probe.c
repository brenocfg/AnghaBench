#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_12__ {struct device_node* of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct TYPE_11__ {int irq; int fifosize; int line; int /*<<< orphan*/  lock; int /*<<< orphan*/  type; int /*<<< orphan*/ * ops; TYPE_4__* dev; int /*<<< orphan*/  uartclk; int /*<<< orphan*/  iotype; struct clk* membase; int /*<<< orphan*/  mapbase; } ;
struct digicolor_port {TYPE_1__ port; int /*<<< orphan*/  rx_poll_work; } ;
struct device_node {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int DIGICOLOR_USART_NR ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  PORT_DIGICOLOR ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  UPIO_MEM ; 
 int /*<<< orphan*/  clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_4__*) ; 
 struct clk* devm_clk_get (TYPE_4__*,int /*<<< orphan*/ *) ; 
 struct clk* devm_ioremap_resource (TYPE_4__*,struct resource*) ; 
 struct digicolor_port* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__** digicolor_ports ; 
 int /*<<< orphan*/  digicolor_rx_poll ; 
 int /*<<< orphan*/  digicolor_uart ; 
 int /*<<< orphan*/  digicolor_uart_int ; 
 int /*<<< orphan*/  digicolor_uart_ops ; 
 int of_alias_get_id (struct device_node*,char*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int uart_add_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int digicolor_uart_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	int irq, ret, index;
	struct digicolor_port *dp;
	struct resource *res;
	struct clk *uart_clk;

	if (!np) {
		dev_err(&pdev->dev, "Missing device tree node\n");
		return -ENXIO;
	}

	index = of_alias_get_id(np, "serial");
	if (index < 0 || index >= DIGICOLOR_USART_NR)
		return -EINVAL;

	dp = devm_kzalloc(&pdev->dev, sizeof(*dp), GFP_KERNEL);
	if (!dp)
		return -ENOMEM;

	uart_clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(uart_clk))
		return PTR_ERR(uart_clk);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	dp->port.mapbase = res->start;
	dp->port.membase = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(dp->port.membase))
		return PTR_ERR(dp->port.membase);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;
	dp->port.irq = irq;

	dp->port.iotype = UPIO_MEM;
	dp->port.uartclk = clk_get_rate(uart_clk);
	dp->port.fifosize = 16;
	dp->port.dev = &pdev->dev;
	dp->port.ops = &digicolor_uart_ops;
	dp->port.line = index;
	dp->port.type = PORT_DIGICOLOR;
	spin_lock_init(&dp->port.lock);

	digicolor_ports[index] = &dp->port;
	platform_set_drvdata(pdev, &dp->port);

	INIT_DELAYED_WORK(&dp->rx_poll_work, digicolor_rx_poll);

	ret = devm_request_irq(&pdev->dev, dp->port.irq, digicolor_uart_int, 0,
			       dev_name(&pdev->dev), &dp->port);
	if (ret)
		return ret;

	return uart_add_one_port(&digicolor_uart, &dp->port);
}