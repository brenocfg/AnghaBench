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
struct uart_port {int irq; TYPE_2__* dev; struct uart_driver* private_data; int /*<<< orphan*/  mapbase; } ;
struct uart_driver {int dummy; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_5__ {struct qcom_geni_serial_port* clk; int /*<<< orphan*/  wrapper; TYPE_2__* dev; } ;
struct qcom_geni_serial_port {int /*<<< orphan*/  handle_rx; int /*<<< orphan*/  tx_fifo_width; void* rx_fifo_depth; void* tx_fifo_depth; TYPE_1__ se; struct uart_port uport; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;

/* Variables and functions */
 void* DEF_FIFO_DEPTH_WORDS ; 
 int /*<<< orphan*/  DEF_FIFO_WIDTH_BITS ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct qcom_geni_serial_port*) ; 
 int PTR_ERR (struct qcom_geni_serial_port*) ; 
 int /*<<< orphan*/  dev_attr_loopback ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_create_file (TYPE_2__*,int /*<<< orphan*/ *) ; 
 struct qcom_geni_serial_port* devm_clk_get (TYPE_2__*,char*) ; 
 struct qcom_geni_serial_port* get_port_from_line (int,int) ; 
 int /*<<< orphan*/  handle_rx_console ; 
 int /*<<< orphan*/  handle_rx_uart ; 
 int of_alias_get_id (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct qcom_geni_serial_port*) ; 
 struct uart_driver qcom_geni_console_driver ; 
 struct uart_driver qcom_geni_uart_driver ; 
 int uart_add_one_port (struct uart_driver*,struct uart_port*) ; 

__attribute__((used)) static int qcom_geni_serial_probe(struct platform_device *pdev)
{
	int ret = 0;
	int line = -1;
	struct qcom_geni_serial_port *port;
	struct uart_port *uport;
	struct resource *res;
	int irq;
	bool console = false;
	struct uart_driver *drv;

	if (of_device_is_compatible(pdev->dev.of_node, "qcom,geni-debug-uart"))
		console = true;

	if (console) {
		drv = &qcom_geni_console_driver;
		line = of_alias_get_id(pdev->dev.of_node, "serial");
	} else {
		drv = &qcom_geni_uart_driver;
		line = of_alias_get_id(pdev->dev.of_node, "hsuart");
	}

	port = get_port_from_line(line, console);
	if (IS_ERR(port)) {
		dev_err(&pdev->dev, "Invalid line %d\n", line);
		return PTR_ERR(port);
	}

	uport = &port->uport;
	/* Don't allow 2 drivers to access the same port */
	if (uport->private_data)
		return -ENODEV;

	uport->dev = &pdev->dev;
	port->se.dev = &pdev->dev;
	port->se.wrapper = dev_get_drvdata(pdev->dev.parent);
	port->se.clk = devm_clk_get(&pdev->dev, "se");
	if (IS_ERR(port->se.clk)) {
		ret = PTR_ERR(port->se.clk);
		dev_err(&pdev->dev, "Err getting SE Core clk %d\n", ret);
		return ret;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -EINVAL;
	uport->mapbase = res->start;

	port->tx_fifo_depth = DEF_FIFO_DEPTH_WORDS;
	port->rx_fifo_depth = DEF_FIFO_DEPTH_WORDS;
	port->tx_fifo_width = DEF_FIFO_WIDTH_BITS;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;
	uport->irq = irq;

	uport->private_data = drv;
	platform_set_drvdata(pdev, port);
	port->handle_rx = console ? handle_rx_console : handle_rx_uart;
	if (!console)
		device_create_file(uport->dev, &dev_attr_loopback);
	return uart_add_one_port(drv, uport);
}