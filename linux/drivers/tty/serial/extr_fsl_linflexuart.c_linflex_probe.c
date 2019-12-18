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
struct uart_port {int line; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; int /*<<< orphan*/  irq; int /*<<< orphan*/  iotype; int /*<<< orphan*/  type; TYPE_1__* dev; int /*<<< orphan*/  membase; int /*<<< orphan*/  mapbase; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_4__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_LINFLEXUART ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int UART_NR ; 
 int /*<<< orphan*/  UPF_BOOT_AUTOCONF ; 
 int /*<<< orphan*/  UPIO_MEM ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct uart_port* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linflex_pops ; 
 struct uart_port** linflex_ports ; 
 int /*<<< orphan*/  linflex_reg ; 
 int of_alias_get_id (struct device_node*,char*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct uart_port*) ; 
 int uart_add_one_port (int /*<<< orphan*/ *,struct uart_port*) ; 

__attribute__((used)) static int linflex_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct uart_port *sport;
	struct resource *res;
	int ret;

	sport = devm_kzalloc(&pdev->dev, sizeof(*sport), GFP_KERNEL);
	if (!sport)
		return -ENOMEM;

	ret = of_alias_get_id(np, "serial");
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to get alias id, errno %d\n", ret);
		return ret;
	}
	if (ret >= UART_NR) {
		dev_err(&pdev->dev, "driver limited to %d serial ports\n",
			UART_NR);
		return -ENOMEM;
	}

	sport->line = ret;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENODEV;

	sport->mapbase = res->start;
	sport->membase = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(sport->membase))
		return PTR_ERR(sport->membase);

	sport->dev = &pdev->dev;
	sport->type = PORT_LINFLEXUART;
	sport->iotype = UPIO_MEM;
	sport->irq = platform_get_irq(pdev, 0);
	sport->ops = &linflex_pops;
	sport->flags = UPF_BOOT_AUTOCONF;

	linflex_ports[sport->line] = sport;

	platform_set_drvdata(pdev, sport);

	ret = uart_add_one_port(&linflex_reg, sport);
	if (ret)
		return ret;

	return 0;
}