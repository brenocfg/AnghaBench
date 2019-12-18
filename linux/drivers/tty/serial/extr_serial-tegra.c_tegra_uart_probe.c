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
struct uart_port {int fifosize; int irq; int regshift; int /*<<< orphan*/  iotype; int /*<<< orphan*/  membase; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  type; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * dev; } ;
struct tegra_uart_port {int /*<<< orphan*/  rst; int /*<<< orphan*/  uart_clk; struct tegra_uart_chip_data const* cdata; struct uart_port uport; } ;
struct tegra_uart_chip_data {int dummy; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct of_device_id {struct tegra_uart_chip_data* data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_TEGRA ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPIO_MEM32 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct tegra_uart_port* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_reset_control_get_exclusive (int /*<<< orphan*/ *,char*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tegra_uart_port*) ; 
 int /*<<< orphan*/  tegra_uart_driver ; 
 int /*<<< orphan*/  tegra_uart_of_match ; 
 int /*<<< orphan*/  tegra_uart_ops ; 
 int tegra_uart_parse_dt (struct platform_device*,struct tegra_uart_port*) ; 
 int uart_add_one_port (int /*<<< orphan*/ *,struct uart_port*) ; 

__attribute__((used)) static int tegra_uart_probe(struct platform_device *pdev)
{
	struct tegra_uart_port *tup;
	struct uart_port *u;
	struct resource *resource;
	int ret;
	const struct tegra_uart_chip_data *cdata;
	const struct of_device_id *match;

	match = of_match_device(tegra_uart_of_match, &pdev->dev);
	if (!match) {
		dev_err(&pdev->dev, "Error: No device match found\n");
		return -ENODEV;
	}
	cdata = match->data;

	tup = devm_kzalloc(&pdev->dev, sizeof(*tup), GFP_KERNEL);
	if (!tup) {
		dev_err(&pdev->dev, "Failed to allocate memory for tup\n");
		return -ENOMEM;
	}

	ret = tegra_uart_parse_dt(pdev, tup);
	if (ret < 0)
		return ret;

	u = &tup->uport;
	u->dev = &pdev->dev;
	u->ops = &tegra_uart_ops;
	u->type = PORT_TEGRA;
	u->fifosize = 32;
	tup->cdata = cdata;

	platform_set_drvdata(pdev, tup);
	resource = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!resource) {
		dev_err(&pdev->dev, "No IO memory resource\n");
		return -ENODEV;
	}

	u->mapbase = resource->start;
	u->membase = devm_ioremap_resource(&pdev->dev, resource);
	if (IS_ERR(u->membase))
		return PTR_ERR(u->membase);

	tup->uart_clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(tup->uart_clk)) {
		dev_err(&pdev->dev, "Couldn't get the clock\n");
		return PTR_ERR(tup->uart_clk);
	}

	tup->rst = devm_reset_control_get_exclusive(&pdev->dev, "serial");
	if (IS_ERR(tup->rst)) {
		dev_err(&pdev->dev, "Couldn't get the reset\n");
		return PTR_ERR(tup->rst);
	}

	u->iotype = UPIO_MEM32;
	ret = platform_get_irq(pdev, 0);
	if (ret < 0)
		return ret;
	u->irq = ret;
	u->regshift = 2;
	ret = uart_add_one_port(&tegra_uart_driver, u);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to add uart port, err %d\n", ret);
		return ret;
	}
	return ret;
}