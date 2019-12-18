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
struct uart_port {scalar_t__ uartclk; int /*<<< orphan*/  lock; int /*<<< orphan*/  mapbase; int /*<<< orphan*/ * membase; int /*<<< orphan*/  irq; int /*<<< orphan*/ * dev; int /*<<< orphan*/  fifosize; int /*<<< orphan*/ * ops; int /*<<< orphan*/  flags; int /*<<< orphan*/  iotype; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct asc_port {int /*<<< orphan*/ ** states; int /*<<< orphan*/ * pinctrl; int /*<<< orphan*/ * clk; struct uart_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASC_FIFO_SIZE ; 
 size_t DEFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IS_ERR (int /*<<< orphan*/ *) ; 
 size_t NO_HW_FLOWCTRL ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UPF_BOOT_AUTOCONF ; 
 int /*<<< orphan*/  UPIO_MEM ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  asc_uart_ops ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 scalar_t__ clk_get_rate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/ * devm_pinctrl_get (int /*<<< orphan*/ *) ; 
 void* pinctrl_lookup_state (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asc_init_port(struct asc_port *ascport,
			  struct platform_device *pdev)
{
	struct uart_port *port = &ascport->port;
	struct resource *res;
	int ret;

	port->iotype	= UPIO_MEM;
	port->flags	= UPF_BOOT_AUTOCONF;
	port->ops	= &asc_uart_ops;
	port->fifosize	= ASC_FIFO_SIZE;
	port->dev	= &pdev->dev;
	port->irq	= platform_get_irq(pdev, 0);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	port->membase = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(port->membase))
		return PTR_ERR(port->membase);
	port->mapbase = res->start;

	spin_lock_init(&port->lock);

	ascport->clk = devm_clk_get(&pdev->dev, NULL);

	if (WARN_ON(IS_ERR(ascport->clk)))
		return -EINVAL;
	/* ensure that clk rate is correct by enabling the clk */
	clk_prepare_enable(ascport->clk);
	ascport->port.uartclk = clk_get_rate(ascport->clk);
	WARN_ON(ascport->port.uartclk == 0);
	clk_disable_unprepare(ascport->clk);

	ascport->pinctrl = devm_pinctrl_get(&pdev->dev);
	if (IS_ERR(ascport->pinctrl)) {
		ret = PTR_ERR(ascport->pinctrl);
		dev_err(&pdev->dev, "Failed to get Pinctrl: %d\n", ret);
		return ret;
	}

	ascport->states[DEFAULT] =
		pinctrl_lookup_state(ascport->pinctrl, "default");
	if (IS_ERR(ascport->states[DEFAULT])) {
		ret = PTR_ERR(ascport->states[DEFAULT]);
		dev_err(&pdev->dev,
			"Failed to look up Pinctrl state 'default': %d\n", ret);
		return ret;
	}

	/* "no-hw-flowctrl" state is optional */
	ascport->states[NO_HW_FLOWCTRL] =
		pinctrl_lookup_state(ascport->pinctrl, "no-hw-flowctrl");
	if (IS_ERR(ascport->states[NO_HW_FLOWCTRL]))
		ascport->states[NO_HW_FLOWCTRL] = NULL;

	return 0;
}