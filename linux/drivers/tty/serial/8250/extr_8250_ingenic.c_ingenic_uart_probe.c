#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; int regshift; int line; int /*<<< orphan*/  uartclk; int /*<<< orphan*/  membase; int /*<<< orphan*/  fifosize; TYPE_2__* dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  serial_in; int /*<<< orphan*/  serial_out; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  iotype; int /*<<< orphan*/  type; int /*<<< orphan*/  lock; } ;
struct uart_8250_port {int capabilities; TYPE_1__ port; int /*<<< orphan*/  tx_loadsz; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct of_device_id {struct ingenic_uart_config* data; } ;
struct ingenic_uart_data {int line; void* clk_module; void* clk_baud; } ;
struct ingenic_uart_config {int /*<<< orphan*/  tx_loadsz; int /*<<< orphan*/  fifosize; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  PORT_16550A ; 
 int PTR_ERR (void*) ; 
 int UART_CAP_FIFO ; 
 int UART_CAP_RTOIE ; 
 int UPF_FIXED_TYPE ; 
 int UPF_IOREMAP ; 
 int UPF_SKIP_TEST ; 
 int /*<<< orphan*/  UPIO_MEM ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int /*<<< orphan*/  clk_get_rate (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 void* devm_clk_get (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ingenic_uart_data* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ingenic_uart_serial_in ; 
 int /*<<< orphan*/  ingenic_uart_serial_out ; 
 int of_alias_get_id (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_match ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ingenic_uart_data*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int serial8250_register_8250_port (struct uart_8250_port*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ingenic_uart_probe(struct platform_device *pdev)
{
	struct uart_8250_port uart = {};
	struct resource *regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	struct resource *irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	struct ingenic_uart_data *data;
	const struct ingenic_uart_config *cdata;
	const struct of_device_id *match;
	int err, line;

	match = of_match_device(of_match, &pdev->dev);
	if (!match) {
		dev_err(&pdev->dev, "Error: No device match found\n");
		return -ENODEV;
	}
	cdata = match->data;

	if (!regs || !irq) {
		dev_err(&pdev->dev, "no registers/irq defined\n");
		return -EINVAL;
	}

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	spin_lock_init(&uart.port.lock);
	uart.port.type = PORT_16550A;
	uart.port.flags = UPF_SKIP_TEST | UPF_IOREMAP | UPF_FIXED_TYPE;
	uart.port.iotype = UPIO_MEM;
	uart.port.mapbase = regs->start;
	uart.port.regshift = 2;
	uart.port.serial_out = ingenic_uart_serial_out;
	uart.port.serial_in = ingenic_uart_serial_in;
	uart.port.irq = irq->start;
	uart.port.dev = &pdev->dev;
	uart.port.fifosize = cdata->fifosize;
	uart.tx_loadsz = cdata->tx_loadsz;
	uart.capabilities = UART_CAP_FIFO | UART_CAP_RTOIE;

	/* Check for a fixed line number */
	line = of_alias_get_id(pdev->dev.of_node, "serial");
	if (line >= 0)
		uart.port.line = line;

	uart.port.membase = devm_ioremap(&pdev->dev, regs->start,
					 resource_size(regs));
	if (!uart.port.membase)
		return -ENOMEM;

	data->clk_module = devm_clk_get(&pdev->dev, "module");
	if (IS_ERR(data->clk_module)) {
		err = PTR_ERR(data->clk_module);
		if (err != -EPROBE_DEFER)
			dev_err(&pdev->dev,
				"unable to get module clock: %d\n", err);
		return err;
	}

	data->clk_baud = devm_clk_get(&pdev->dev, "baud");
	if (IS_ERR(data->clk_baud)) {
		err = PTR_ERR(data->clk_baud);
		if (err != -EPROBE_DEFER)
			dev_err(&pdev->dev,
				"unable to get baud clock: %d\n", err);
		return err;
	}

	err = clk_prepare_enable(data->clk_module);
	if (err) {
		dev_err(&pdev->dev, "could not enable module clock: %d\n", err);
		goto out;
	}

	err = clk_prepare_enable(data->clk_baud);
	if (err) {
		dev_err(&pdev->dev, "could not enable baud clock: %d\n", err);
		goto out_disable_moduleclk;
	}
	uart.port.uartclk = clk_get_rate(data->clk_baud);

	data->line = serial8250_register_8250_port(&uart);
	if (data->line < 0) {
		err = data->line;
		goto out_disable_baudclk;
	}

	platform_set_drvdata(pdev, data);
	return 0;

out_disable_baudclk:
	clk_disable_unprepare(data->clk_baud);
out_disable_moduleclk:
	clk_disable_unprepare(data->clk_module);
out:
	return err;
}