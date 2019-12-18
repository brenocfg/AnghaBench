#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uart ;
struct TYPE_9__ {int line; int irq; int regshift; int flags; int /*<<< orphan*/  serial_out; int /*<<< orphan*/  rs485_config; struct lpc18xx_uart_data* private_data; int /*<<< orphan*/  uartclk; int /*<<< orphan*/  type; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  iotype; TYPE_5__* dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  membase; } ;
struct uart_8250_port {TYPE_4__* dma; TYPE_1__ port; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_13__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_5__ dev; } ;
struct TYPE_11__ {int dst_maxburst; } ;
struct TYPE_10__ {int src_maxburst; } ;
struct TYPE_12__ {TYPE_3__ txconf; TYPE_2__ rxconf; struct lpc18xx_uart_data* tx_param; struct lpc18xx_uart_data* rx_param; } ;
struct lpc18xx_uart_data {int line; void* clk_reg; void* clk_uart; TYPE_4__ dma; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  PORT_16550A ; 
 int PTR_ERR (void*) ; 
 int UPF_FIXED_PORT ; 
 int UPF_FIXED_TYPE ; 
 int UPF_SKIP_TEST ; 
 int /*<<< orphan*/  UPIO_MEM32 ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int /*<<< orphan*/  clk_get_rate (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*) ; 
 void* devm_clk_get (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lpc18xx_uart_data* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpc18xx_rs485_config ; 
 int /*<<< orphan*/  lpc18xx_uart_serial_out ; 
 int /*<<< orphan*/  memset (struct uart_8250_port*,int /*<<< orphan*/ ,int) ; 
 int of_alias_get_id (int /*<<< orphan*/ ,char*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lpc18xx_uart_data*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int serial8250_register_8250_port (struct uart_8250_port*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lpc18xx_serial_probe(struct platform_device *pdev)
{
	struct lpc18xx_uart_data *data;
	struct uart_8250_port uart;
	struct resource *res;
	int irq, ret;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "memory resource not found");
		return -EINVAL;
	}

	memset(&uart, 0, sizeof(uart));

	uart.port.membase = devm_ioremap(&pdev->dev, res->start,
					 resource_size(res));
	if (!uart.port.membase)
		return -ENOMEM;

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->clk_uart = devm_clk_get(&pdev->dev, "uartclk");
	if (IS_ERR(data->clk_uart)) {
		dev_err(&pdev->dev, "uart clock not found\n");
		return PTR_ERR(data->clk_uart);
	}

	data->clk_reg = devm_clk_get(&pdev->dev, "reg");
	if (IS_ERR(data->clk_reg)) {
		dev_err(&pdev->dev, "reg clock not found\n");
		return PTR_ERR(data->clk_reg);
	}

	ret = clk_prepare_enable(data->clk_reg);
	if (ret) {
		dev_err(&pdev->dev, "unable to enable reg clock\n");
		return ret;
	}

	ret = clk_prepare_enable(data->clk_uart);
	if (ret) {
		dev_err(&pdev->dev, "unable to enable uart clock\n");
		goto dis_clk_reg;
	}

	ret = of_alias_get_id(pdev->dev.of_node, "serial");
	if (ret >= 0)
		uart.port.line = ret;

	data->dma.rx_param = data;
	data->dma.tx_param = data;

	spin_lock_init(&uart.port.lock);
	uart.port.dev = &pdev->dev;
	uart.port.irq = irq;
	uart.port.iotype = UPIO_MEM32;
	uart.port.mapbase = res->start;
	uart.port.regshift = 2;
	uart.port.type = PORT_16550A;
	uart.port.flags = UPF_FIXED_PORT | UPF_FIXED_TYPE | UPF_SKIP_TEST;
	uart.port.uartclk = clk_get_rate(data->clk_uart);
	uart.port.private_data = data;
	uart.port.rs485_config = lpc18xx_rs485_config;
	uart.port.serial_out = lpc18xx_uart_serial_out;

	uart.dma = &data->dma;
	uart.dma->rxconf.src_maxburst = 1;
	uart.dma->txconf.dst_maxburst = 1;

	ret = serial8250_register_8250_port(&uart);
	if (ret < 0) {
		dev_err(&pdev->dev, "unable to register 8250 port\n");
		goto dis_uart_clk;
	}

	data->line = ret;
	platform_set_drvdata(pdev, data);

	return 0;

dis_uart_clk:
	clk_disable_unprepare(data->clk_uart);
dis_clk_reg:
	clk_disable_unprepare(data->clk_reg);
	return ret;
}