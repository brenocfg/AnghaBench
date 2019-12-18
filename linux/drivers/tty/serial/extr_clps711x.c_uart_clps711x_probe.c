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
struct device_node {int dummy; } ;
struct TYPE_11__ {int irq; int fifosize; int flags; int /*<<< orphan*/ * ops; int /*<<< orphan*/  uartclk; int /*<<< orphan*/  type; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  iotype; TYPE_4__* dev; int /*<<< orphan*/  line; struct clk* membase; } ;
struct clps711x_port {int rx_irq; int tx_enabled; TYPE_1__ port; struct clk* syscon; struct clk* gpios; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  PORT_CLPS711X ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  SYSCON_OFFSET ; 
 int /*<<< orphan*/  SYSCON_UARTEN ; 
 int UPF_FIXED_TYPE ; 
 int UPF_SKIP_TEST ; 
 int /*<<< orphan*/  UPIO_MEM32 ; 
 int /*<<< orphan*/  clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  clps711x_uart ; 
 int /*<<< orphan*/  dev_name (TYPE_4__*) ; 
 struct clk* devm_clk_get (TYPE_4__*,int /*<<< orphan*/ *) ; 
 struct clk* devm_ioremap_resource (TYPE_4__*,struct resource*) ; 
 struct clps711x_port* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct clk* mctrl_gpio_init_noauto (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_alias_get_id (struct device_node*,char*) ; 
 void* platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct clps711x_port*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct clk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 
 int uart_add_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  uart_clps711x_int_rx ; 
 int /*<<< orphan*/  uart_clps711x_int_tx ; 
 int /*<<< orphan*/  uart_clps711x_ops ; 
 int /*<<< orphan*/  uart_console (TYPE_1__*) ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int uart_clps711x_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct clps711x_port *s;
	struct resource *res;
	struct clk *uart_clk;
	int irq, ret;

	s = devm_kzalloc(&pdev->dev, sizeof(*s), GFP_KERNEL);
	if (!s)
		return -ENOMEM;

	uart_clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(uart_clk))
		return PTR_ERR(uart_clk);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	s->port.membase = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(s->port.membase))
		return PTR_ERR(s->port.membase);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;
	s->port.irq = irq;

	s->rx_irq = platform_get_irq(pdev, 1);
	if (s->rx_irq < 0)
		return s->rx_irq;

	s->syscon = syscon_regmap_lookup_by_phandle(np, "syscon");
	if (IS_ERR(s->syscon))
		return PTR_ERR(s->syscon);

	s->port.line		= of_alias_get_id(np, "serial");
	s->port.dev		= &pdev->dev;
	s->port.iotype		= UPIO_MEM32;
	s->port.mapbase		= res->start;
	s->port.type		= PORT_CLPS711X;
	s->port.fifosize	= 16;
	s->port.flags		= UPF_SKIP_TEST | UPF_FIXED_TYPE;
	s->port.uartclk		= clk_get_rate(uart_clk);
	s->port.ops		= &uart_clps711x_ops;

	platform_set_drvdata(pdev, s);

	s->gpios = mctrl_gpio_init_noauto(&pdev->dev, 0);
	if (IS_ERR(s->gpios))
	    return PTR_ERR(s->gpios);

	ret = uart_add_one_port(&clps711x_uart, &s->port);
	if (ret)
		return ret;

	/* Disable port */
	if (!uart_console(&s->port))
		regmap_update_bits(s->syscon, SYSCON_OFFSET, SYSCON_UARTEN, 0);

	s->tx_enabled = 1;

	ret = devm_request_irq(&pdev->dev, s->port.irq, uart_clps711x_int_tx, 0,
			       dev_name(&pdev->dev), &s->port);
	if (ret) {
		uart_remove_one_port(&clps711x_uart, &s->port);
		return ret;
	}

	ret = devm_request_irq(&pdev->dev, s->rx_irq, uart_clps711x_int_rx, 0,
			       dev_name(&pdev->dev), &s->port);
	if (ret)
		uart_remove_one_port(&clps711x_uart, &s->port);

	return ret;
}