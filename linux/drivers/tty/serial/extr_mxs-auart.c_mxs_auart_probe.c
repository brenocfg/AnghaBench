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
typedef  int u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {size_t id; int /*<<< orphan*/  dev; TYPE_1__* id_entry; } ;
struct of_device_id {TYPE_1__* data; } ;
struct TYPE_4__ {size_t line; int irq; int /*<<< orphan*/  type; int /*<<< orphan*/  uartclk; int /*<<< orphan*/  fifosize; int /*<<< orphan*/  iotype; int /*<<< orphan*/ * ops; int /*<<< orphan*/  membase; int /*<<< orphan*/  mapbase; int /*<<< orphan*/ * dev; } ;
struct mxs_auart_port {int /*<<< orphan*/  clk_ahb; int /*<<< orphan*/  clk; TYPE_2__ port; scalar_t__ mctrl_prev; int /*<<< orphan*/  devtype; int /*<<< orphan*/ * dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  driver_data; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct mxs_auart_port**) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  MXS_AUART_FIFO_SIZE ; 
 int /*<<< orphan*/  PORT_IMX ; 
 int /*<<< orphan*/  REG_VERSION ; 
 int /*<<< orphan*/  UPIO_MEM ; 
 int /*<<< orphan*/  auart_driver ; 
 struct mxs_auart_port** auart_port ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct mxs_auart_port* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mxs_auart_port*) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_asm9260_auart (struct mxs_auart_port*) ; 
 int /*<<< orphan*/  mxs_auart_dt_ids ; 
 int /*<<< orphan*/  mxs_auart_free_gpio_irq (struct mxs_auart_port*) ; 
 int mxs_auart_init_gpios (struct mxs_auart_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxs_auart_irq_handle ; 
 int /*<<< orphan*/  mxs_auart_ops ; 
 int mxs_auart_request_gpio_irq (struct mxs_auart_port*) ; 
 int /*<<< orphan*/  mxs_auart_reset_deassert (struct mxs_auart_port*) ; 
 int mxs_get_clks (struct mxs_auart_port*,struct platform_device*) ; 
 int /*<<< orphan*/  mxs_init_regs (struct mxs_auart_port*) ; 
 int mxs_read (struct mxs_auart_port*,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mxs_auart_port*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int serial_mxs_probe_dt (struct mxs_auart_port*,struct platform_device*) ; 
 int uart_add_one_port (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int mxs_auart_probe(struct platform_device *pdev)
{
	const struct of_device_id *of_id =
			of_match_device(mxs_auart_dt_ids, &pdev->dev);
	struct mxs_auart_port *s;
	u32 version;
	int ret, irq;
	struct resource *r;

	s = devm_kzalloc(&pdev->dev, sizeof(*s), GFP_KERNEL);
	if (!s)
		return -ENOMEM;

	s->port.dev = &pdev->dev;
	s->dev = &pdev->dev;

	ret = serial_mxs_probe_dt(s, pdev);
	if (ret > 0)
		s->port.line = pdev->id < 0 ? 0 : pdev->id;
	else if (ret < 0)
		return ret;
	if (s->port.line >= ARRAY_SIZE(auart_port)) {
		dev_err(&pdev->dev, "serial%d out of range\n", s->port.line);
		return -EINVAL;
	}

	if (of_id) {
		pdev->id_entry = of_id->data;
		s->devtype = pdev->id_entry->driver_data;
	}

	ret = mxs_get_clks(s, pdev);
	if (ret)
		return ret;

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!r) {
		ret = -ENXIO;
		goto out_disable_clks;
	}

	s->port.mapbase = r->start;
	s->port.membase = ioremap(r->start, resource_size(r));
	if (!s->port.membase) {
		ret = -ENOMEM;
		goto out_disable_clks;
	}
	s->port.ops = &mxs_auart_ops;
	s->port.iotype = UPIO_MEM;
	s->port.fifosize = MXS_AUART_FIFO_SIZE;
	s->port.uartclk = clk_get_rate(s->clk);
	s->port.type = PORT_IMX;

	mxs_init_regs(s);

	s->mctrl_prev = 0;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		ret = irq;
		goto out_disable_clks;
	}

	s->port.irq = irq;
	ret = devm_request_irq(&pdev->dev, irq, mxs_auart_irq_handle, 0,
			       dev_name(&pdev->dev), s);
	if (ret)
		goto out_disable_clks;

	platform_set_drvdata(pdev, s);

	ret = mxs_auart_init_gpios(s, &pdev->dev);
	if (ret) {
		dev_err(&pdev->dev, "Failed to initialize GPIOs.\n");
		goto out_disable_clks;
	}

	/*
	 * Get the GPIO lines IRQ
	 */
	ret = mxs_auart_request_gpio_irq(s);
	if (ret)
		goto out_disable_clks;

	auart_port[s->port.line] = s;

	mxs_auart_reset_deassert(s);

	ret = uart_add_one_port(&auart_driver, &s->port);
	if (ret)
		goto out_free_qpio_irq;

	/* ASM9260 don't have version reg */
	if (is_asm9260_auart(s)) {
		dev_info(&pdev->dev, "Found APPUART ASM9260\n");
	} else {
		version = mxs_read(s, REG_VERSION);
		dev_info(&pdev->dev, "Found APPUART %d.%d.%d\n",
			 (version >> 24) & 0xff,
			 (version >> 16) & 0xff, version & 0xffff);
	}

	return 0;

out_free_qpio_irq:
	mxs_auart_free_gpio_irq(s);
	auart_port[pdev->id] = NULL;

out_disable_clks:
	if (is_asm9260_auart(s)) {
		clk_disable_unprepare(s->clk);
		clk_disable_unprepare(s->clk_ahb);
	}
	return ret;
}