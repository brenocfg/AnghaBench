#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct uart_port {size_t line; TYPE_4__* dev; int /*<<< orphan*/  lock; int /*<<< orphan*/ * ops; int /*<<< orphan*/  uartclk; int /*<<< orphan*/  irq; int /*<<< orphan*/  membase; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  fifosize; struct sirfsoc_uart_port* private_data; int /*<<< orphan*/  flags; int /*<<< orphan*/  iotype; } ;
struct sirfsoc_uart_register {int /*<<< orphan*/  uart_type; } ;
struct TYPE_12__ {int /*<<< orphan*/  buf; scalar_t__ tail; scalar_t__ head; } ;
struct TYPE_13__ {int /*<<< orphan*/  dma_addr; TYPE_1__ xmit; } ;
struct TYPE_14__ {int /*<<< orphan*/  function; } ;
struct sirfsoc_uart_port {int hw_flow_ctrl; int cts_gpio; int rts_gpio; int is_atlas7; int is_hrt_enabled; void* rx_dma_chan; TYPE_2__ rx_dma_items; TYPE_3__ hrt; void* tx_dma_chan; int /*<<< orphan*/  clk; struct sirfsoc_uart_register* uart_reg; struct uart_port port; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_15__ {struct device_node* of_node; } ;
struct platform_device {int /*<<< orphan*/  id; TYPE_4__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct dma_slave_config {int src_maxburst; int dst_maxburst; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct sirfsoc_uart_port**) ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIRFSOC_RX_DMA_BUF_SIZE ; 
 int /*<<< orphan*/  SIRF_REAL_UART ; 
 int /*<<< orphan*/  SIRF_USP_UART ; 
 int /*<<< orphan*/  UPF_BOOT_AUTOCONF ; 
 int /*<<< orphan*/  UPIO_MEM ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int devm_gpio_request (TYPE_4__*,int,char*) ; 
 int /*<<< orphan*/  devm_ioremap (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sirfsoc_uart_port* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_alloc_coherent (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (void*) ; 
 void* dma_request_slave_channel (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  dmaengine_slave_config (void*,struct dma_slave_config*) ; 
 int /*<<< orphan*/  gpio_direction_input (int) ; 
 int /*<<< orphan*/  gpio_direction_output (int,int) ; 
 int /*<<< orphan*/  gpio_is_valid (int) ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t of_alias_get_id (struct device_node*,char*) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 scalar_t__ of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 void* of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,struct device_node*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sirfsoc_uart_port*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 struct sirfsoc_uart_port** sirf_ports ; 
 int /*<<< orphan*/  sirfsoc_uart_drv ; 
 int /*<<< orphan*/  sirfsoc_uart_ids ; 
 int /*<<< orphan*/  sirfsoc_uart_ops ; 
 int /*<<< orphan*/  sirfsoc_uart_rx_dma_hrtimer_callback ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int uart_add_one_port (int /*<<< orphan*/ *,struct uart_port*) ; 

__attribute__((used)) static int sirfsoc_uart_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct sirfsoc_uart_port *sirfport;
	struct uart_port *port;
	struct resource *res;
	int ret;
	struct dma_slave_config slv_cfg = {
		.src_maxburst = 1,
	};
	struct dma_slave_config tx_slv_cfg = {
		.dst_maxburst = 2,
	};
	const struct of_device_id *match;

	match = of_match_node(sirfsoc_uart_ids, np);
	sirfport = devm_kzalloc(&pdev->dev, sizeof(*sirfport), GFP_KERNEL);
	if (!sirfport) {
		ret = -ENOMEM;
		goto err;
	}
	sirfport->port.line = of_alias_get_id(np, "serial");
	if (sirfport->port.line >= ARRAY_SIZE(sirf_ports)) {
		dev_err(&pdev->dev, "serial%d out of range\n",
			sirfport->port.line);
		return -EINVAL;
	}
	sirf_ports[sirfport->port.line] = sirfport;
	sirfport->port.iotype = UPIO_MEM;
	sirfport->port.flags = UPF_BOOT_AUTOCONF;
	port = &sirfport->port;
	port->dev = &pdev->dev;
	port->private_data = sirfport;
	sirfport->uart_reg = (struct sirfsoc_uart_register *)match->data;

	sirfport->hw_flow_ctrl =
		of_property_read_bool(np, "uart-has-rtscts") ||
		of_property_read_bool(np, "sirf,uart-has-rtscts") /* deprecated */;
	if (of_device_is_compatible(np, "sirf,prima2-uart") ||
		of_device_is_compatible(np, "sirf,atlas7-uart"))
		sirfport->uart_reg->uart_type = SIRF_REAL_UART;
	if (of_device_is_compatible(np, "sirf,prima2-usp-uart") ||
	    of_device_is_compatible(np, "sirf,atlas7-usp-uart")) {
		sirfport->uart_reg->uart_type =	SIRF_USP_UART;
		if (!sirfport->hw_flow_ctrl)
			goto usp_no_flow_control;
		if (of_find_property(np, "cts-gpios", NULL))
			sirfport->cts_gpio =
				of_get_named_gpio(np, "cts-gpios", 0);
		else
			sirfport->cts_gpio = -1;
		if (of_find_property(np, "rts-gpios", NULL))
			sirfport->rts_gpio =
				of_get_named_gpio(np, "rts-gpios", 0);
		else
			sirfport->rts_gpio = -1;

		if ((!gpio_is_valid(sirfport->cts_gpio) ||
			 !gpio_is_valid(sirfport->rts_gpio))) {
			ret = -EINVAL;
			dev_err(&pdev->dev,
				"Usp flow control must have cts and rts gpio");
			goto err;
		}
		ret = devm_gpio_request(&pdev->dev, sirfport->cts_gpio,
				"usp-cts-gpio");
		if (ret) {
			dev_err(&pdev->dev, "Unable request cts gpio");
			goto err;
		}
		gpio_direction_input(sirfport->cts_gpio);
		ret = devm_gpio_request(&pdev->dev, sirfport->rts_gpio,
				"usp-rts-gpio");
		if (ret) {
			dev_err(&pdev->dev, "Unable request rts gpio");
			goto err;
		}
		gpio_direction_output(sirfport->rts_gpio, 1);
	}
usp_no_flow_control:
	if (of_device_is_compatible(np, "sirf,atlas7-uart") ||
	    of_device_is_compatible(np, "sirf,atlas7-usp-uart"))
		sirfport->is_atlas7 = true;

	if (of_property_read_u32(np, "fifosize", &port->fifosize)) {
		dev_err(&pdev->dev,
			"Unable to find fifosize in uart node.\n");
		ret = -EFAULT;
		goto err;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		dev_err(&pdev->dev, "Insufficient resources.\n");
		ret = -EFAULT;
		goto err;
	}
	port->mapbase = res->start;
	port->membase = devm_ioremap(&pdev->dev,
			res->start, resource_size(res));
	if (!port->membase) {
		dev_err(&pdev->dev, "Cannot remap resource.\n");
		ret = -ENOMEM;
		goto err;
	}
	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (res == NULL) {
		dev_err(&pdev->dev, "Insufficient resources.\n");
		ret = -EFAULT;
		goto err;
	}
	port->irq = res->start;

	sirfport->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(sirfport->clk)) {
		ret = PTR_ERR(sirfport->clk);
		goto err;
	}
	port->uartclk = clk_get_rate(sirfport->clk);

	port->ops = &sirfsoc_uart_ops;
	spin_lock_init(&port->lock);

	platform_set_drvdata(pdev, sirfport);
	ret = uart_add_one_port(&sirfsoc_uart_drv, port);
	if (ret != 0) {
		dev_err(&pdev->dev, "Cannot add UART port(%d).\n", pdev->id);
		goto err;
	}

	sirfport->rx_dma_chan = dma_request_slave_channel(port->dev, "rx");
	sirfport->rx_dma_items.xmit.buf =
		dma_alloc_coherent(port->dev, SIRFSOC_RX_DMA_BUF_SIZE,
		&sirfport->rx_dma_items.dma_addr, GFP_KERNEL);
	if (!sirfport->rx_dma_items.xmit.buf) {
		dev_err(port->dev, "Uart alloc bufa failed\n");
		ret = -ENOMEM;
		goto alloc_coherent_err;
	}
	sirfport->rx_dma_items.xmit.head =
		sirfport->rx_dma_items.xmit.tail = 0;
	if (sirfport->rx_dma_chan)
		dmaengine_slave_config(sirfport->rx_dma_chan, &slv_cfg);
	sirfport->tx_dma_chan = dma_request_slave_channel(port->dev, "tx");
	if (sirfport->tx_dma_chan)
		dmaengine_slave_config(sirfport->tx_dma_chan, &tx_slv_cfg);
	if (sirfport->rx_dma_chan) {
		hrtimer_init(&sirfport->hrt, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
		sirfport->hrt.function = sirfsoc_uart_rx_dma_hrtimer_callback;
		sirfport->is_hrt_enabled = false;
	}

	return 0;
alloc_coherent_err:
	dma_free_coherent(port->dev, SIRFSOC_RX_DMA_BUF_SIZE,
			sirfport->rx_dma_items.xmit.buf,
			sirfport->rx_dma_items.dma_addr);
	dma_release_channel(sirfport->rx_dma_chan);
err:
	return ret;
}