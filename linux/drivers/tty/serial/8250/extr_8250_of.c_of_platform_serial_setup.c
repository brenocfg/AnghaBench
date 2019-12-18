#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct uart_port {int custom_divisor; int flags; int iobase; int mapbase; int regshift; int fifosize; int line; int irq; int type; int uartclk; int /*<<< orphan*/  handle_irq; void* iotype; int /*<<< orphan*/  handle_break; TYPE_1__* dev; int /*<<< orphan*/  irqflags; int /*<<< orphan*/  mapsize; int /*<<< orphan*/  lock; } ;
struct resource {int start; } ;
struct TYPE_8__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_serial_info {int /*<<< orphan*/  clk; int /*<<< orphan*/  rst; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SERIAL_8250_FSL ; 
 int EINVAL ; 
 int EPROBE_DEFER ; 
 scalar_t__ IORESOURCE_IO ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
#define  PORT_RT2880 129 
#define  PORT_TEGRA 128 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int UPF_BOOT_AUTOCONF ; 
 int UPF_FIXED_PORT ; 
 int UPF_FIXED_TYPE ; 
 int UPF_IOREMAP ; 
 int UPF_SHARE_IRQ ; 
 int UPF_SKIP_TEST ; 
 void* UPIO_AU ; 
 void* UPIO_MEM ; 
 void* UPIO_MEM16 ; 
 void* UPIO_MEM32 ; 
 void* UPIO_MEM32BE ; 
 void* UPIO_PORT ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_reset_control_get_optional_shared (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl8250_handle_irq ; 
 int /*<<< orphan*/  memset (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 int of_alias_get_id (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_device_is_big_endian (struct device_node*) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 int of_irq_get (struct device_node*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (TYPE_1__*) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 scalar_t__ resource_type (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_serial_handle_break ; 

__attribute__((used)) static int of_platform_serial_setup(struct platform_device *ofdev,
			int type, struct uart_port *port,
			struct of_serial_info *info)
{
	struct resource resource;
	struct device_node *np = ofdev->dev.of_node;
	u32 clk, spd, prop;
	int ret, irq;

	memset(port, 0, sizeof *port);

	pm_runtime_enable(&ofdev->dev);
	pm_runtime_get_sync(&ofdev->dev);

	if (of_property_read_u32(np, "clock-frequency", &clk)) {

		/* Get clk rate through clk driver if present */
		info->clk = devm_clk_get(&ofdev->dev, NULL);
		if (IS_ERR(info->clk)) {
			ret = PTR_ERR(info->clk);
			if (ret != -EPROBE_DEFER)
				dev_warn(&ofdev->dev,
					 "failed to get clock: %d\n", ret);
			goto err_pmruntime;
		}

		ret = clk_prepare_enable(info->clk);
		if (ret < 0)
			goto err_pmruntime;

		clk = clk_get_rate(info->clk);
	}
	/* If current-speed was set, then try not to change it. */
	if (of_property_read_u32(np, "current-speed", &spd) == 0)
		port->custom_divisor = clk / (16 * spd);

	ret = of_address_to_resource(np, 0, &resource);
	if (ret) {
		dev_warn(&ofdev->dev, "invalid address\n");
		goto err_unprepare;
	}

	port->flags = UPF_SHARE_IRQ | UPF_BOOT_AUTOCONF | UPF_FIXED_PORT |
				  UPF_FIXED_TYPE;
	spin_lock_init(&port->lock);

	if (resource_type(&resource) == IORESOURCE_IO) {
		port->iotype = UPIO_PORT;
		port->iobase = resource.start;
	} else {
		port->mapbase = resource.start;
		port->mapsize = resource_size(&resource);

		/* Check for shifted address mapping */
		if (of_property_read_u32(np, "reg-offset", &prop) == 0)
			port->mapbase += prop;

		port->iotype = UPIO_MEM;
		if (of_property_read_u32(np, "reg-io-width", &prop) == 0) {
			switch (prop) {
			case 1:
				port->iotype = UPIO_MEM;
				break;
			case 2:
				port->iotype = UPIO_MEM16;
				break;
			case 4:
				port->iotype = of_device_is_big_endian(np) ?
					       UPIO_MEM32BE : UPIO_MEM32;
				break;
			default:
				dev_warn(&ofdev->dev, "unsupported reg-io-width (%d)\n",
					 prop);
				ret = -EINVAL;
				goto err_unprepare;
			}
		}
		port->flags |= UPF_IOREMAP;
	}

	/* Compatibility with the deprecated pxa driver and 8250_pxa drivers. */
	if (of_device_is_compatible(np, "mrvl,mmp-uart"))
		port->regshift = 2;

	/* Check for registers offset within the devices address range */
	if (of_property_read_u32(np, "reg-shift", &prop) == 0)
		port->regshift = prop;

	/* Check for fifo size */
	if (of_property_read_u32(np, "fifo-size", &prop) == 0)
		port->fifosize = prop;

	/* Check for a fixed line number */
	ret = of_alias_get_id(np, "serial");
	if (ret >= 0)
		port->line = ret;

	irq = of_irq_get(np, 0);
	if (irq < 0) {
		if (irq == -EPROBE_DEFER) {
			ret = -EPROBE_DEFER;
			goto err_unprepare;
		}
		/* IRQ support not mandatory */
		irq = 0;
	}

	port->irq = irq;

	info->rst = devm_reset_control_get_optional_shared(&ofdev->dev, NULL);
	if (IS_ERR(info->rst)) {
		ret = PTR_ERR(info->rst);
		goto err_unprepare;
	}

	ret = reset_control_deassert(info->rst);
	if (ret)
		goto err_unprepare;

	port->type = type;
	port->uartclk = clk;
	port->irqflags |= IRQF_SHARED;

	if (of_property_read_bool(np, "no-loopback-test"))
		port->flags |= UPF_SKIP_TEST;

	port->dev = &ofdev->dev;

	switch (type) {
	case PORT_TEGRA:
		port->handle_break = tegra_serial_handle_break;
		break;

	case PORT_RT2880:
		port->iotype = UPIO_AU;
		break;
	}

	if (IS_ENABLED(CONFIG_SERIAL_8250_FSL) &&
	    (of_device_is_compatible(np, "fsl,ns16550") ||
	     of_device_is_compatible(np, "fsl,16550-FIFO64")))
		port->handle_irq = fsl8250_handle_irq;

	return 0;
err_unprepare:
	clk_disable_unprepare(info->clk);
err_pmruntime:
	pm_runtime_put_sync(&ofdev->dev);
	pm_runtime_disable(&ofdev->dev);
	return ret;
}