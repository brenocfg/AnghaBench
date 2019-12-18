#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct uart_port {int irq; int flags; int regshift; int uartclk; int fifosize; int /*<<< orphan*/ * handle_irq; int /*<<< orphan*/  serial_out; int /*<<< orphan*/  serial_in; int /*<<< orphan*/  iotype; TYPE_4__* private_data; int /*<<< orphan*/  membase; int /*<<< orphan*/  set_termios; int /*<<< orphan*/  set_ldisc; struct device* dev; int /*<<< orphan*/  type; int /*<<< orphan*/  pm; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  lock; } ;
struct uart_8250_port {TYPE_3__* dma; struct uart_port port; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_6__ {int dst_maxburst; } ;
struct TYPE_5__ {int src_maxburst; } ;
struct TYPE_7__ {TYPE_2__ txconf; TYPE_1__ rxconf; int /*<<< orphan*/  fn; } ;
struct TYPE_8__ {int line; TYPE_3__ dma; } ;
struct dw8250_data {void* clk; void* pclk; void* rst; TYPE_4__ data; int /*<<< orphan*/  skip_autocfg; scalar_t__ uart_16550_compatible; int /*<<< orphan*/  msr_mask_off; int /*<<< orphan*/  msr_mask_on; int /*<<< orphan*/  usr_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_UART_USR ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (void*) ; 
 int /*<<< orphan*/  PORT_8250 ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  UART_MSR_CTS ; 
 int /*<<< orphan*/  UART_MSR_DCD ; 
 int /*<<< orphan*/  UART_MSR_DCTS ; 
 int /*<<< orphan*/  UART_MSR_DDCD ; 
 int /*<<< orphan*/  UART_MSR_DDSR ; 
 int /*<<< orphan*/  UART_MSR_DSR ; 
 int /*<<< orphan*/  UART_MSR_RI ; 
 int /*<<< orphan*/  UART_MSR_TERI ; 
 int UPF_FIXED_PORT ; 
 int UPF_SHARE_IRQ ; 
 int /*<<< orphan*/  UPIO_MEM ; 
 int /*<<< orphan*/  UPIO_MEM32 ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_get_rate (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 scalar_t__ device_property_read_bool (struct device*,char*) ; 
 int device_property_read_u32 (struct device*,char*,int*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dw8250_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_reset_control_get_optional_exclusive (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dw8250_do_pm ; 
 int /*<<< orphan*/  dw8250_fallback_dma_filter ; 
 int /*<<< orphan*/ * dw8250_handle_irq ; 
 int /*<<< orphan*/  dw8250_quirks (struct uart_port*,struct dw8250_data*) ; 
 int /*<<< orphan*/  dw8250_serial_in ; 
 int /*<<< orphan*/  dw8250_serial_in32 ; 
 int /*<<< orphan*/  dw8250_serial_out ; 
 int /*<<< orphan*/  dw8250_serial_out32 ; 
 int /*<<< orphan*/  dw8250_set_ldisc ; 
 int /*<<< orphan*/  dw8250_set_termios ; 
 int /*<<< orphan*/  dw8250_setup_port (struct uart_port*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct dw8250_data*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  reset_control_assert (void*) ; 
 int /*<<< orphan*/  reset_control_deassert (void*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int serial8250_register_8250_port (struct uart_8250_port*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dw8250_probe(struct platform_device *pdev)
{
	struct uart_8250_port uart = {}, *up = &uart;
	struct resource *regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	int irq = platform_get_irq(pdev, 0);
	struct uart_port *p = &up->port;
	struct device *dev = &pdev->dev;
	struct dw8250_data *data;
	int err;
	u32 val;

	if (!regs) {
		dev_err(dev, "no registers defined\n");
		return -EINVAL;
	}

	if (irq < 0) {
		if (irq != -EPROBE_DEFER)
			dev_err(dev, "cannot get irq\n");
		return irq;
	}

	spin_lock_init(&p->lock);
	p->mapbase	= regs->start;
	p->irq		= irq;
	p->handle_irq	= dw8250_handle_irq;
	p->pm		= dw8250_do_pm;
	p->type		= PORT_8250;
	p->flags	= UPF_SHARE_IRQ | UPF_FIXED_PORT;
	p->dev		= dev;
	p->iotype	= UPIO_MEM;
	p->serial_in	= dw8250_serial_in;
	p->serial_out	= dw8250_serial_out;
	p->set_ldisc	= dw8250_set_ldisc;
	p->set_termios	= dw8250_set_termios;

	p->membase = devm_ioremap(dev, regs->start, resource_size(regs));
	if (!p->membase)
		return -ENOMEM;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->data.dma.fn = dw8250_fallback_dma_filter;
	data->usr_reg = DW_UART_USR;
	p->private_data = &data->data;

	data->uart_16550_compatible = device_property_read_bool(dev,
						"snps,uart-16550-compatible");

	err = device_property_read_u32(dev, "reg-shift", &val);
	if (!err)
		p->regshift = val;

	err = device_property_read_u32(dev, "reg-io-width", &val);
	if (!err && val == 4) {
		p->iotype = UPIO_MEM32;
		p->serial_in = dw8250_serial_in32;
		p->serial_out = dw8250_serial_out32;
	}

	if (device_property_read_bool(dev, "dcd-override")) {
		/* Always report DCD as active */
		data->msr_mask_on |= UART_MSR_DCD;
		data->msr_mask_off |= UART_MSR_DDCD;
	}

	if (device_property_read_bool(dev, "dsr-override")) {
		/* Always report DSR as active */
		data->msr_mask_on |= UART_MSR_DSR;
		data->msr_mask_off |= UART_MSR_DDSR;
	}

	if (device_property_read_bool(dev, "cts-override")) {
		/* Always report CTS as active */
		data->msr_mask_on |= UART_MSR_CTS;
		data->msr_mask_off |= UART_MSR_DCTS;
	}

	if (device_property_read_bool(dev, "ri-override")) {
		/* Always report Ring indicator as inactive */
		data->msr_mask_off |= UART_MSR_RI;
		data->msr_mask_off |= UART_MSR_TERI;
	}

	/* Always ask for fixed clock rate from a property. */
	device_property_read_u32(dev, "clock-frequency", &p->uartclk);

	/* If there is separate baudclk, get the rate from it. */
	data->clk = devm_clk_get(dev, "baudclk");
	if (IS_ERR(data->clk) && PTR_ERR(data->clk) != -EPROBE_DEFER)
		data->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(data->clk) && PTR_ERR(data->clk) == -EPROBE_DEFER)
		return -EPROBE_DEFER;
	if (!IS_ERR_OR_NULL(data->clk)) {
		err = clk_prepare_enable(data->clk);
		if (err)
			dev_warn(dev, "could not enable optional baudclk: %d\n",
				 err);
		else
			p->uartclk = clk_get_rate(data->clk);
	}

	/* If no clock rate is defined, fail. */
	if (!p->uartclk) {
		dev_err(dev, "clock rate not defined\n");
		err = -EINVAL;
		goto err_clk;
	}

	data->pclk = devm_clk_get(dev, "apb_pclk");
	if (IS_ERR(data->pclk) && PTR_ERR(data->pclk) == -EPROBE_DEFER) {
		err = -EPROBE_DEFER;
		goto err_clk;
	}
	if (!IS_ERR(data->pclk)) {
		err = clk_prepare_enable(data->pclk);
		if (err) {
			dev_err(dev, "could not enable apb_pclk\n");
			goto err_clk;
		}
	}

	data->rst = devm_reset_control_get_optional_exclusive(dev, NULL);
	if (IS_ERR(data->rst)) {
		err = PTR_ERR(data->rst);
		goto err_pclk;
	}
	reset_control_deassert(data->rst);

	dw8250_quirks(p, data);

	/* If the Busy Functionality is not implemented, don't handle it */
	if (data->uart_16550_compatible)
		p->handle_irq = NULL;

	if (!data->skip_autocfg)
		dw8250_setup_port(p);

	/* If we have a valid fifosize, try hooking up DMA */
	if (p->fifosize) {
		data->data.dma.rxconf.src_maxburst = p->fifosize / 4;
		data->data.dma.txconf.dst_maxburst = p->fifosize / 4;
		up->dma = &data->data.dma;
	}

	data->data.line = serial8250_register_8250_port(up);
	if (data->data.line < 0) {
		err = data->data.line;
		goto err_reset;
	}

	platform_set_drvdata(pdev, data);

	pm_runtime_set_active(dev);
	pm_runtime_enable(dev);

	return 0;

err_reset:
	reset_control_assert(data->rst);

err_pclk:
	if (!IS_ERR(data->pclk))
		clk_disable_unprepare(data->pclk);

err_clk:
	if (!IS_ERR(data->clk))
		clk_disable_unprepare(data->clk);

	return err;
}