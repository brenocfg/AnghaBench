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
struct uart_port {unsigned int line; int type; int flags; int regshift; scalar_t__ irq; int /*<<< orphan*/  serial_out; int /*<<< orphan*/  serial_in; scalar_t__ irqflags; int /*<<< orphan*/  fifosize; int /*<<< orphan*/ * dev; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  iotype; int /*<<< orphan*/ * ops; } ;
struct sci_port {int reg_size; scalar_t__* irqs; int rx_trigger; TYPE_1__* params; int /*<<< orphan*/  sampling_rate_mask; scalar_t__ hscif_tot; scalar_t__ rx_fifo_timeout; struct plat_sci_port const* cfg; struct uart_port port; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct plat_sci_port {int type; int flags; scalar_t__ sampling_rate; int /*<<< orphan*/  regtype; } ;
struct TYPE_2__ {int /*<<< orphan*/  fifosize; int /*<<< orphan*/  sampling_rate_mask; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
#define  PORT_HSCIF 131 
 int PORT_SCI ; 
#define  PORT_SCIF 130 
#define  PORT_SCIFA 129 
#define  PORT_SCIFB 128 
 int /*<<< orphan*/  SCI_SR (scalar_t__) ; 
 size_t SCIx_RXI_IRQ ; 
 int /*<<< orphan*/  SCIx_SH7705_SCIF_REGTYPE ; 
 int UPF_BOOT_AUTOCONF ; 
 int UPF_FIXED_PORT ; 
 int /*<<< orphan*/  UPIO_MEM ; 
 scalar_t__ platform_get_irq (struct platform_device*,unsigned int) ; 
 scalar_t__ platform_get_irq_optional (struct platform_device*,unsigned int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int resource_size (struct resource const*) ; 
 int sci_init_clocks (struct sci_port*,int /*<<< orphan*/ *) ; 
 TYPE_1__* sci_probe_regmap (struct plat_sci_port const*) ; 
 int /*<<< orphan*/  sci_serial_in ; 
 int /*<<< orphan*/  sci_serial_out ; 
 int /*<<< orphan*/  sci_uart_ops ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sci_init_single(struct platform_device *dev,
			   struct sci_port *sci_port, unsigned int index,
			   const struct plat_sci_port *p, bool early)
{
	struct uart_port *port = &sci_port->port;
	const struct resource *res;
	unsigned int i;
	int ret;

	sci_port->cfg	= p;

	port->ops	= &sci_uart_ops;
	port->iotype	= UPIO_MEM;
	port->line	= index;

	res = platform_get_resource(dev, IORESOURCE_MEM, 0);
	if (res == NULL)
		return -ENOMEM;

	port->mapbase = res->start;
	sci_port->reg_size = resource_size(res);

	for (i = 0; i < ARRAY_SIZE(sci_port->irqs); ++i) {
		if (i)
			sci_port->irqs[i] = platform_get_irq_optional(dev, i);
		else
			sci_port->irqs[i] = platform_get_irq(dev, i);
	}

	/* The SCI generates several interrupts. They can be muxed together or
	 * connected to different interrupt lines. In the muxed case only one
	 * interrupt resource is specified as there is only one interrupt ID.
	 * In the non-muxed case, up to 6 interrupt signals might be generated
	 * from the SCI, however those signals might have their own individual
	 * interrupt ID numbers, or muxed together with another interrupt.
	 */
	if (sci_port->irqs[0] < 0)
		return -ENXIO;

	if (sci_port->irqs[1] < 0)
		for (i = 1; i < ARRAY_SIZE(sci_port->irqs); i++)
			sci_port->irqs[i] = sci_port->irqs[0];

	sci_port->params = sci_probe_regmap(p);
	if (unlikely(sci_port->params == NULL))
		return -EINVAL;

	switch (p->type) {
	case PORT_SCIFB:
		sci_port->rx_trigger = 48;
		break;
	case PORT_HSCIF:
		sci_port->rx_trigger = 64;
		break;
	case PORT_SCIFA:
		sci_port->rx_trigger = 32;
		break;
	case PORT_SCIF:
		if (p->regtype == SCIx_SH7705_SCIF_REGTYPE)
			/* RX triggering not implemented for this IP */
			sci_port->rx_trigger = 1;
		else
			sci_port->rx_trigger = 8;
		break;
	default:
		sci_port->rx_trigger = 1;
		break;
	}

	sci_port->rx_fifo_timeout = 0;
	sci_port->hscif_tot = 0;

	/* SCIFA on sh7723 and sh7724 need a custom sampling rate that doesn't
	 * match the SoC datasheet, this should be investigated. Let platform
	 * data override the sampling rate for now.
	 */
	sci_port->sampling_rate_mask = p->sampling_rate
				     ? SCI_SR(p->sampling_rate)
				     : sci_port->params->sampling_rate_mask;

	if (!early) {
		ret = sci_init_clocks(sci_port, &dev->dev);
		if (ret < 0)
			return ret;

		port->dev = &dev->dev;

		pm_runtime_enable(&dev->dev);
	}

	port->type		= p->type;
	port->flags		= UPF_FIXED_PORT | UPF_BOOT_AUTOCONF | p->flags;
	port->fifosize		= sci_port->params->fifosize;

	if (port->type == PORT_SCI) {
		if (sci_port->reg_size >= 0x20)
			port->regshift = 2;
		else
			port->regshift = 1;
	}

	/*
	 * The UART port needs an IRQ value, so we peg this to the RX IRQ
	 * for the multi-IRQ ports, which is where we are primarily
	 * concerned with the shutdown path synchronization.
	 *
	 * For the muxed case there's nothing more to do.
	 */
	port->irq		= sci_port->irqs[SCIx_RXI_IRQ];
	port->irqflags		= 0;

	port->serial_in		= sci_serial_in;
	port->serial_out	= sci_serial_out;

	return 0;
}