#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int fifosize; void* irq; int /*<<< orphan*/  uartclk; int /*<<< orphan*/ * dev; int /*<<< orphan*/ * ops; int /*<<< orphan*/  flags; int /*<<< orphan*/  iotype; int /*<<< orphan*/  mapsize; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  membase; } ;
struct mps2_uart_port {int flags; TYPE_1__ port; void* tx_irq; void* rx_irq; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int UART_PORT_COMBINED_IRQ ; 
 int /*<<< orphan*/  UPF_BOOT_AUTOCONF ; 
 int /*<<< orphan*/  UPIO_MEM ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  mps2_uart_pops ; 
 void* platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int mps2_init_port(struct platform_device *pdev,
			  struct mps2_uart_port *mps_port)
{
	struct resource *res;
	int ret;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	mps_port->port.membase = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(mps_port->port.membase))
		return PTR_ERR(mps_port->port.membase);

	mps_port->port.mapbase = res->start;
	mps_port->port.mapsize = resource_size(res);
	mps_port->port.iotype = UPIO_MEM;
	mps_port->port.flags = UPF_BOOT_AUTOCONF;
	mps_port->port.fifosize = 1;
	mps_port->port.ops = &mps2_uart_pops;
	mps_port->port.dev = &pdev->dev;

	mps_port->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(mps_port->clk))
		return PTR_ERR(mps_port->clk);

	ret = clk_prepare_enable(mps_port->clk);
	if (ret)
		return ret;

	mps_port->port.uartclk = clk_get_rate(mps_port->clk);

	clk_disable_unprepare(mps_port->clk);


	if (mps_port->flags & UART_PORT_COMBINED_IRQ) {
		mps_port->port.irq = platform_get_irq(pdev, 0);
	} else {
		mps_port->rx_irq = platform_get_irq(pdev, 0);
		mps_port->tx_irq = platform_get_irq(pdev, 1);
		mps_port->port.irq = platform_get_irq(pdev, 2);
	}

	return ret;
}