#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_17__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {struct lpuart_soc_data* data; } ;
struct lpuart_soc_data {int /*<<< orphan*/  iotype; int /*<<< orphan*/  devtype; scalar_t__ reg_off; } ;
struct TYPE_18__ {int flags; scalar_t__ delay_rts_after_send; scalar_t__ delay_rts_before_send; } ;
struct TYPE_20__ {int line; int irq; TYPE_1__* dev; TYPE_2__ rs485; int /*<<< orphan*/  uartclk; int /*<<< orphan*/  (* rs485_config ) (TYPE_4__*,TYPE_2__*) ;int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; int /*<<< orphan*/  iotype; int /*<<< orphan*/  type; int /*<<< orphan*/  mapbase; int /*<<< orphan*/ * membase; } ;
struct lpuart_port {TYPE_4__ port; void* dma_rx_chan; void* dma_tx_chan; int /*<<< orphan*/ * baud_clk; int /*<<< orphan*/ * ipg_clk; int /*<<< orphan*/  devtype; } ;
struct device_node {int dummy; } ;
struct TYPE_19__ {int /*<<< orphan*/  cons; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct lpuart_port**) ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LPUART32_CONSOLE ; 
 int /*<<< orphan*/  LPUART_CONSOLE ; 
 int /*<<< orphan*/  PORT_LPUART ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int SER_RS485_RX_DURING_TX ; 
 int /*<<< orphan*/  UART_NR ; 
 int /*<<< orphan*/  UPF_BOOT_AUTOCONF ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 void* devm_clk_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct lpuart_port* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lpuart_port*) ; 
 void* dma_request_slave_channel (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  fsl_lpuart_ida ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_imx8qxp_lpuart (struct lpuart_port*) ; 
 int /*<<< orphan*/  lpuart32_int ; 
 int /*<<< orphan*/  lpuart32_pops ; 
 int /*<<< orphan*/  lpuart_config_rs485 (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  lpuart_disable_clks (struct lpuart_port*) ; 
 int /*<<< orphan*/  lpuart_dt_ids ; 
 int lpuart_enable_clks (struct lpuart_port*) ; 
 int /*<<< orphan*/  lpuart_get_baud_clk_rate (struct lpuart_port*) ; 
 int /*<<< orphan*/  lpuart_int ; 
 scalar_t__ lpuart_is_32 (struct lpuart_port*) ; 
 int /*<<< orphan*/  lpuart_pops ; 
 struct lpuart_port** lpuart_ports ; 
 TYPE_3__ lpuart_reg ; 
 int of_alias_get_id (struct device_node*,char*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_4__*) ; 
 int uart_add_one_port (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  uart_get_rs485_mode (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int lpuart_probe(struct platform_device *pdev)
{
	const struct of_device_id *of_id = of_match_device(lpuart_dt_ids,
							   &pdev->dev);
	const struct lpuart_soc_data *sdata = of_id->data;
	struct device_node *np = pdev->dev.of_node;
	struct lpuart_port *sport;
	struct resource *res;
	int ret;

	sport = devm_kzalloc(&pdev->dev, sizeof(*sport), GFP_KERNEL);
	if (!sport)
		return -ENOMEM;

	ret = of_alias_get_id(np, "serial");
	if (ret < 0) {
		ret = ida_simple_get(&fsl_lpuart_ida, 0, UART_NR, GFP_KERNEL);
		if (ret < 0) {
			dev_err(&pdev->dev, "port line is full, add device failed\n");
			return ret;
		}
	}
	if (ret >= ARRAY_SIZE(lpuart_ports)) {
		dev_err(&pdev->dev, "serial%d out of range\n", ret);
		return -EINVAL;
	}
	sport->port.line = ret;
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	sport->port.membase = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(sport->port.membase))
		return PTR_ERR(sport->port.membase);

	sport->port.membase += sdata->reg_off;
	sport->port.mapbase = res->start;
	sport->port.dev = &pdev->dev;
	sport->port.type = PORT_LPUART;
	sport->devtype = sdata->devtype;
	ret = platform_get_irq(pdev, 0);
	if (ret < 0)
		return ret;
	sport->port.irq = ret;
	sport->port.iotype = sdata->iotype;
	if (lpuart_is_32(sport))
		sport->port.ops = &lpuart32_pops;
	else
		sport->port.ops = &lpuart_pops;
	sport->port.flags = UPF_BOOT_AUTOCONF;

	sport->port.rs485_config = lpuart_config_rs485;

	sport->ipg_clk = devm_clk_get(&pdev->dev, "ipg");
	if (IS_ERR(sport->ipg_clk)) {
		ret = PTR_ERR(sport->ipg_clk);
		dev_err(&pdev->dev, "failed to get uart ipg clk: %d\n", ret);
		return ret;
	}

	sport->baud_clk = NULL;
	if (is_imx8qxp_lpuart(sport)) {
		sport->baud_clk = devm_clk_get(&pdev->dev, "baud");
		if (IS_ERR(sport->baud_clk)) {
			ret = PTR_ERR(sport->baud_clk);
			dev_err(&pdev->dev, "failed to get uart baud clk: %d\n", ret);
			return ret;
		}
	}

	ret = lpuart_enable_clks(sport);
	if (ret)
		return ret;
	sport->port.uartclk = lpuart_get_baud_clk_rate(sport);

	lpuart_ports[sport->port.line] = sport;

	platform_set_drvdata(pdev, &sport->port);

	if (lpuart_is_32(sport)) {
		lpuart_reg.cons = LPUART32_CONSOLE;
		ret = devm_request_irq(&pdev->dev, sport->port.irq, lpuart32_int, 0,
					DRIVER_NAME, sport);
	} else {
		lpuart_reg.cons = LPUART_CONSOLE;
		ret = devm_request_irq(&pdev->dev, sport->port.irq, lpuart_int, 0,
					DRIVER_NAME, sport);
	}

	if (ret)
		goto failed_irq_request;

	ret = uart_add_one_port(&lpuart_reg, &sport->port);
	if (ret)
		goto failed_attach_port;

	uart_get_rs485_mode(&pdev->dev, &sport->port.rs485);

	if (sport->port.rs485.flags & SER_RS485_RX_DURING_TX)
		dev_err(&pdev->dev, "driver doesn't support RX during TX\n");

	if (sport->port.rs485.delay_rts_before_send ||
	    sport->port.rs485.delay_rts_after_send)
		dev_err(&pdev->dev, "driver doesn't support RTS delays\n");

	lpuart_config_rs485(&sport->port, &sport->port.rs485);

	sport->dma_tx_chan = dma_request_slave_channel(sport->port.dev, "tx");
	if (!sport->dma_tx_chan)
		dev_info(sport->port.dev, "DMA tx channel request failed, "
				"operating without tx DMA\n");

	sport->dma_rx_chan = dma_request_slave_channel(sport->port.dev, "rx");
	if (!sport->dma_rx_chan)
		dev_info(sport->port.dev, "DMA rx channel request failed, "
				"operating without rx DMA\n");

	return 0;

failed_attach_port:
failed_irq_request:
	lpuart_disable_clks(sport);
	return ret;
}