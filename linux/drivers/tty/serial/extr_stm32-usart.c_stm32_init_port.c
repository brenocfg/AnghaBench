#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int irq; int /*<<< orphan*/  uartclk; int /*<<< orphan*/  lock; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  membase; int /*<<< orphan*/  rs485_config; int /*<<< orphan*/  fifosize; int /*<<< orphan*/ * dev; int /*<<< orphan*/ * ops; int /*<<< orphan*/  flags; int /*<<< orphan*/  iotype; } ;
struct stm32_port {int wakeirq; int /*<<< orphan*/  clk; struct uart_port port; TYPE_2__* info; int /*<<< orphan*/  fifoen; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  has_fifo; scalar_t__ has_wakeup; int /*<<< orphan*/  fifosize; } ;
struct TYPE_4__ {TYPE_1__ cfg; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPF_BOOT_AUTOCONF ; 
 int /*<<< orphan*/  UPIO_MEM ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 void* platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_config_rs485 ; 
 int /*<<< orphan*/  stm32_init_rs485 (struct uart_port*,struct platform_device*) ; 
 int /*<<< orphan*/  stm32_uart_ops ; 

__attribute__((used)) static int stm32_init_port(struct stm32_port *stm32port,
			  struct platform_device *pdev)
{
	struct uart_port *port = &stm32port->port;
	struct resource *res;
	int ret;

	port->iotype	= UPIO_MEM;
	port->flags	= UPF_BOOT_AUTOCONF;
	port->ops	= &stm32_uart_ops;
	port->dev	= &pdev->dev;
	port->fifosize	= stm32port->info->cfg.fifosize;

	ret = platform_get_irq(pdev, 0);
	if (ret <= 0)
		return ret ? : -ENODEV;
	port->irq = ret;

	port->rs485_config = stm32_config_rs485;

	stm32_init_rs485(port, pdev);

	if (stm32port->info->cfg.has_wakeup) {
		stm32port->wakeirq = platform_get_irq(pdev, 1);
		if (stm32port->wakeirq <= 0 && stm32port->wakeirq != -ENXIO)
			return stm32port->wakeirq ? : -ENODEV;
	}

	stm32port->fifoen = stm32port->info->cfg.has_fifo;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	port->membase = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(port->membase))
		return PTR_ERR(port->membase);
	port->mapbase = res->start;

	spin_lock_init(&port->lock);

	stm32port->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(stm32port->clk))
		return PTR_ERR(stm32port->clk);

	/* Ensure that clk rate is correct by enabling the clk */
	ret = clk_prepare_enable(stm32port->clk);
	if (ret)
		return ret;

	stm32port->port.uartclk = clk_get_rate(stm32port->clk);
	if (!stm32port->port.uartclk) {
		clk_disable_unprepare(stm32port->clk);
		ret = -EINVAL;
	}

	return ret;
}