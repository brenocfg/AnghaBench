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
struct uart_port {int irq; int fifosize; int flags; int line; TYPE_1__* dev; int /*<<< orphan*/ * ops; int /*<<< orphan*/  iotype; int /*<<< orphan*/  uartclk; int /*<<< orphan*/  membase; void* private_data; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 size_t RX ; 
 size_t TX ; 
 int UPF_BOOT_AUTOCONF ; 
 int UPF_SPD_VHI ; 
 int /*<<< orphan*/  UPIO_MEM32 ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 int /*<<< orphan*/  clk_get_rate (struct clk*) ; 
 int clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct clk* devm_clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int** mlb_usio_irq ; 
 int /*<<< orphan*/  mlb_usio_ops ; 
 struct uart_port* mlb_usio_ports ; 
 int /*<<< orphan*/  mlb_usio_uart_driver ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int uart_add_one_port (int /*<<< orphan*/ *,struct uart_port*) ; 

__attribute__((used)) static int mlb_usio_probe(struct platform_device *pdev)
{
	struct clk *clk = devm_clk_get(&pdev->dev, NULL);
	struct uart_port *port;
	struct resource *res;
	int index = 0;
	int ret;

	if (IS_ERR(clk)) {
		dev_err(&pdev->dev, "Missing clock\n");
		return PTR_ERR(clk);
	}
	ret = clk_prepare_enable(clk);
	if (ret) {
		dev_err(&pdev->dev, "Clock enable failed: %d\n", ret);
		return ret;
	}
	of_property_read_u32(pdev->dev.of_node, "index", &index);
	port = &mlb_usio_ports[index];

	port->private_data = (void *)clk;
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		dev_err(&pdev->dev, "Missing regs\n");
		ret = -ENODEV;
		goto failed;
	}
	port->membase = devm_ioremap(&pdev->dev, res->start,
				resource_size(res));

	ret = platform_get_irq_byname(pdev, "rx");
	mlb_usio_irq[index][RX] = ret;

	ret = platform_get_irq_byname(pdev, "tx");
	mlb_usio_irq[index][TX] = ret;

	port->irq = mlb_usio_irq[index][RX];
	port->uartclk = clk_get_rate(clk);
	port->fifosize = 128;
	port->iotype = UPIO_MEM32;
	port->flags = UPF_BOOT_AUTOCONF | UPF_SPD_VHI;
	port->line = index;
	port->ops = &mlb_usio_ops;
	port->dev = &pdev->dev;

	ret = uart_add_one_port(&mlb_usio_uart_driver, port);
	if (ret) {
		dev_err(&pdev->dev, "Adding port failed: %d\n", ret);
		goto failed;
	}
	return 0;

failed:
	clk_disable_unprepare(clk);

	return ret;
}