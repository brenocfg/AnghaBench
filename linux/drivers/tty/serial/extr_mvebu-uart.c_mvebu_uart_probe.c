#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int fifosize; size_t line; scalar_t__ membase; int /*<<< orphan*/  uartclk; struct mvebu_uart* private_data; int /*<<< orphan*/  mapbase; scalar_t__ irqflags; int /*<<< orphan*/  irq; int /*<<< orphan*/  flags; int /*<<< orphan*/  iotype; scalar_t__ regshift; int /*<<< orphan*/ * ops; int /*<<< orphan*/  type; TYPE_1__* dev; int /*<<< orphan*/  lock; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {int id; TYPE_1__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct mvebu_uart_driver_data {int dummy; } ;
struct mvebu_uart {int* irq; scalar_t__ clk; struct uart_port* port; struct mvebu_uart_driver_data* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_SOFT_RST ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 scalar_t__ IS_EXTENDED (struct uart_port*) ; 
 int MVEBU_NR_UARTS ; 
 int /*<<< orphan*/  PORT_MVEBU ; 
 int PTR_ERR (scalar_t__) ; 
 scalar_t__ UART_CTRL (struct uart_port*) ; 
 size_t UART_IRQ_SUM ; 
 size_t UART_RX_IRQ ; 
 size_t UART_TX_IRQ ; 
 int /*<<< orphan*/  UPF_FIXED_PORT ; 
 int /*<<< orphan*/  UPIO_MEM32 ; 
 int /*<<< orphan*/  clk_get_rate (scalar_t__) ; 
 int /*<<< orphan*/  clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 scalar_t__ devm_clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct mvebu_uart* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvebu_uart_driver ; 
 int /*<<< orphan*/  mvebu_uart_of_match ; 
 int /*<<< orphan*/  mvebu_uart_ops ; 
 struct uart_port* mvebu_uart_ports ; 
 int of_alias_get_id (int /*<<< orphan*/ ,char*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int platform_irq_count (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mvebu_uart*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int uart_add_one_port (int /*<<< orphan*/ *,struct uart_port*) ; 
 int /*<<< orphan*/  uart_num_counter ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int mvebu_uart_probe(struct platform_device *pdev)
{
	struct resource *reg = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	const struct of_device_id *match = of_match_device(mvebu_uart_of_match,
							   &pdev->dev);
	struct uart_port *port;
	struct mvebu_uart *mvuart;
	int ret, id, irq;

	if (!reg) {
		dev_err(&pdev->dev, "no registers defined\n");
		return -EINVAL;
	}

	if (!match)
		return -ENODEV;

	/* Assume that all UART ports have a DT alias or none has */
	id = of_alias_get_id(pdev->dev.of_node, "serial");
	if (!pdev->dev.of_node || id < 0)
		pdev->id = uart_num_counter++;
	else
		pdev->id = id;

	if (pdev->id >= MVEBU_NR_UARTS) {
		dev_err(&pdev->dev, "cannot have more than %d UART ports\n",
			MVEBU_NR_UARTS);
		return -EINVAL;
	}

	port = &mvebu_uart_ports[pdev->id];

	spin_lock_init(&port->lock);

	port->dev        = &pdev->dev;
	port->type       = PORT_MVEBU;
	port->ops        = &mvebu_uart_ops;
	port->regshift   = 0;

	port->fifosize   = 32;
	port->iotype     = UPIO_MEM32;
	port->flags      = UPF_FIXED_PORT;
	port->line       = pdev->id;

	/*
	 * IRQ number is not stored in this structure because we may have two of
	 * them per port (RX and TX). Instead, use the driver UART structure
	 * array so called ->irq[].
	 */
	port->irq        = 0;
	port->irqflags   = 0;
	port->mapbase    = reg->start;

	port->membase = devm_ioremap_resource(&pdev->dev, reg);
	if (IS_ERR(port->membase))
		return -PTR_ERR(port->membase);

	mvuart = devm_kzalloc(&pdev->dev, sizeof(struct mvebu_uart),
			      GFP_KERNEL);
	if (!mvuart)
		return -ENOMEM;

	/* Get controller data depending on the compatible string */
	mvuart->data = (struct mvebu_uart_driver_data *)match->data;
	mvuart->port = port;

	port->private_data = mvuart;
	platform_set_drvdata(pdev, mvuart);

	/* Get fixed clock frequency */
	mvuart->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(mvuart->clk)) {
		if (PTR_ERR(mvuart->clk) == -EPROBE_DEFER)
			return PTR_ERR(mvuart->clk);

		if (IS_EXTENDED(port)) {
			dev_err(&pdev->dev, "unable to get UART clock\n");
			return PTR_ERR(mvuart->clk);
		}
	} else {
		if (!clk_prepare_enable(mvuart->clk))
			port->uartclk = clk_get_rate(mvuart->clk);
	}

	/* Manage interrupts */
	if (platform_irq_count(pdev) == 1) {
		/* Old bindings: no name on the single unamed UART0 IRQ */
		irq = platform_get_irq(pdev, 0);
		if (irq < 0)
			return irq;

		mvuart->irq[UART_IRQ_SUM] = irq;
	} else {
		/*
		 * New bindings: named interrupts (RX, TX) for both UARTS,
		 * only make use of uart-rx and uart-tx interrupts, do not use
		 * uart-sum of UART0 port.
		 */
		irq = platform_get_irq_byname(pdev, "uart-rx");
		if (irq < 0)
			return irq;

		mvuart->irq[UART_RX_IRQ] = irq;

		irq = platform_get_irq_byname(pdev, "uart-tx");
		if (irq < 0)
			return irq;

		mvuart->irq[UART_TX_IRQ] = irq;
	}

	/* UART Soft Reset*/
	writel(CTRL_SOFT_RST, port->membase + UART_CTRL(port));
	udelay(1);
	writel(0, port->membase + UART_CTRL(port));

	ret = uart_add_one_port(&mvebu_uart_driver, port);
	if (ret)
		return ret;
	return 0;
}