#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  long u32 ;
struct sched_param {int sched_priority; } ;
struct TYPE_10__ {int base; int can_sleep; scalar_t__ ngpio; int /*<<< orphan*/  set; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  label; struct device* parent; int /*<<< orphan*/  owner; } ;
struct sc16is7xx_port {struct regmap* clk; struct regmap* kworker_task; TYPE_6__ gpio; TYPE_1__* p; struct regmap* regmap; int /*<<< orphan*/  kworker; int /*<<< orphan*/  irq_work; int /*<<< orphan*/  efr_lock; struct sc16is7xx_devtype const* devtype; } ;
struct sc16is7xx_devtype {int nr_uart; scalar_t__ nr_gpio; } ;
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_9__ {int irq; int flags; unsigned long uartclk; scalar_t__ line; int /*<<< orphan*/ * ops; int /*<<< orphan*/  rs485_config; int /*<<< orphan*/  iotype; int /*<<< orphan*/  fifosize; int /*<<< orphan*/  type; struct device* dev; } ;
struct TYPE_8__ {int line; TYPE_2__ port; int /*<<< orphan*/  reg_work; int /*<<< orphan*/  tx_work; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int MAX_RT_PRIO ; 
 int /*<<< orphan*/  PORT_SC16IS7XX ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  SC16IS7XX_EFCR_REG ; 
 int SC16IS7XX_EFCR_RXDISABLE_BIT ; 
 int SC16IS7XX_EFCR_TXDISABLE_BIT ; 
 int SC16IS7XX_EFR_ENABLE_BIT ; 
 int /*<<< orphan*/  SC16IS7XX_EFR_REG ; 
 int /*<<< orphan*/  SC16IS7XX_FIFO_SIZE ; 
 int /*<<< orphan*/  SC16IS7XX_IER_REG ; 
 int SC16IS7XX_IOCONTROL_REG ; 
 int /*<<< orphan*/  SC16IS7XX_IOCONTROL_SRESET_BIT ; 
 int SC16IS7XX_LCR_CONF_MODE_B ; 
 int /*<<< orphan*/  SC16IS7XX_LCR_REG ; 
 scalar_t__ SC16IS7XX_MAX_DEVS ; 
 int SC16IS7XX_REG_SHIFT ; 
 int /*<<< orphan*/  SCHED_FIFO ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int UPF_FIXED_TYPE ; 
 int UPF_LOW_LATENCY ; 
 int /*<<< orphan*/  UPIO_PORT ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct regmap*) ; 
 unsigned long clk_get_rate (struct regmap*) ; 
 int clk_prepare_enable (struct regmap*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned long) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 unsigned long* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct sc16is7xx_port*) ; 
 int /*<<< orphan*/  device_property_read_u32 (struct device*,char*,long*) ; 
 struct regmap* devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct sc16is7xx_port* devm_kzalloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct sc16is7xx_port*) ; 
 int gpiochip_add_data (TYPE_6__*,struct sc16is7xx_port*) ; 
 int /*<<< orphan*/  gpiochip_remove (TYPE_6__*) ; 
 int /*<<< orphan*/  kthread_init_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_init_worker (int /*<<< orphan*/ *) ; 
 struct regmap* kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kthread_stop (struct regmap*) ; 
 int /*<<< orphan*/  kthread_worker_fn ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p ; 
 int /*<<< orphan*/  regcache_cache_bypass (struct regmap*,int) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sc16is7xx_alloc_line () ; 
 int /*<<< orphan*/  sc16is7xx_config_rs485 ; 
 int /*<<< orphan*/  sc16is7xx_gpio_direction_input ; 
 int /*<<< orphan*/  sc16is7xx_gpio_direction_output ; 
 int /*<<< orphan*/  sc16is7xx_gpio_get ; 
 int /*<<< orphan*/  sc16is7xx_gpio_set ; 
 int /*<<< orphan*/  sc16is7xx_irq ; 
 int /*<<< orphan*/  sc16is7xx_ist ; 
 int /*<<< orphan*/  sc16is7xx_lines ; 
 int /*<<< orphan*/  sc16is7xx_ops ; 
 int /*<<< orphan*/  sc16is7xx_port_write (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sc16is7xx_power (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc16is7xx_reg_proc ; 
 int /*<<< orphan*/  sc16is7xx_tx_proc ; 
 int /*<<< orphan*/  sc16is7xx_uart ; 
 int /*<<< orphan*/  sched_setscheduler (struct regmap*,int /*<<< orphan*/ ,struct sched_param*) ; 
 int /*<<< orphan*/  struct_size (struct sc16is7xx_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_add_one_port (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int sc16is7xx_probe(struct device *dev,
			   const struct sc16is7xx_devtype *devtype,
			   struct regmap *regmap, int irq, unsigned long flags)
{
	struct sched_param sched_param = { .sched_priority = MAX_RT_PRIO / 2 };
	unsigned long freq = 0, *pfreq = dev_get_platdata(dev);
	u32 uartclk = 0;
	int i, ret;
	struct sc16is7xx_port *s;

	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	/* Alloc port structure */
	s = devm_kzalloc(dev, struct_size(s, p, devtype->nr_uart), GFP_KERNEL);
	if (!s) {
		dev_err(dev, "Error allocating port structure\n");
		return -ENOMEM;
	}

	/* Always ask for fixed clock rate from a property. */
	device_property_read_u32(dev, "clock-frequency", &uartclk);

	s->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(s->clk)) {
		if (uartclk)
			freq = uartclk;
		if (pfreq)
			freq = *pfreq;
		if (freq)
			dev_dbg(dev, "Clock frequency: %luHz\n", freq);
		else
			return PTR_ERR(s->clk);
	} else {
		ret = clk_prepare_enable(s->clk);
		if (ret)
			return ret;

		freq = clk_get_rate(s->clk);
	}

	s->regmap = regmap;
	s->devtype = devtype;
	dev_set_drvdata(dev, s);
	mutex_init(&s->efr_lock);

	kthread_init_worker(&s->kworker);
	kthread_init_work(&s->irq_work, sc16is7xx_ist);
	s->kworker_task = kthread_run(kthread_worker_fn, &s->kworker,
				      "sc16is7xx");
	if (IS_ERR(s->kworker_task)) {
		ret = PTR_ERR(s->kworker_task);
		goto out_clk;
	}
	sched_setscheduler(s->kworker_task, SCHED_FIFO, &sched_param);

#ifdef CONFIG_GPIOLIB
	if (devtype->nr_gpio) {
		/* Setup GPIO cotroller */
		s->gpio.owner		 = THIS_MODULE;
		s->gpio.parent		 = dev;
		s->gpio.label		 = dev_name(dev);
		s->gpio.direction_input	 = sc16is7xx_gpio_direction_input;
		s->gpio.get		 = sc16is7xx_gpio_get;
		s->gpio.direction_output = sc16is7xx_gpio_direction_output;
		s->gpio.set		 = sc16is7xx_gpio_set;
		s->gpio.base		 = -1;
		s->gpio.ngpio		 = devtype->nr_gpio;
		s->gpio.can_sleep	 = 1;
		ret = gpiochip_add_data(&s->gpio, s);
		if (ret)
			goto out_thread;
	}
#endif

	/* reset device, purging any pending irq / data */
	regmap_write(s->regmap, SC16IS7XX_IOCONTROL_REG << SC16IS7XX_REG_SHIFT,
			SC16IS7XX_IOCONTROL_SRESET_BIT);

	for (i = 0; i < devtype->nr_uart; ++i) {
		s->p[i].line		= i;
		/* Initialize port data */
		s->p[i].port.dev	= dev;
		s->p[i].port.irq	= irq;
		s->p[i].port.type	= PORT_SC16IS7XX;
		s->p[i].port.fifosize	= SC16IS7XX_FIFO_SIZE;
		s->p[i].port.flags	= UPF_FIXED_TYPE | UPF_LOW_LATENCY;
		s->p[i].port.iotype	= UPIO_PORT;
		s->p[i].port.uartclk	= freq;
		s->p[i].port.rs485_config = sc16is7xx_config_rs485;
		s->p[i].port.ops	= &sc16is7xx_ops;
		s->p[i].port.line	= sc16is7xx_alloc_line();
		if (s->p[i].port.line >= SC16IS7XX_MAX_DEVS) {
			ret = -ENOMEM;
			goto out_ports;
		}

		/* Disable all interrupts */
		sc16is7xx_port_write(&s->p[i].port, SC16IS7XX_IER_REG, 0);
		/* Disable TX/RX */
		sc16is7xx_port_write(&s->p[i].port, SC16IS7XX_EFCR_REG,
				     SC16IS7XX_EFCR_RXDISABLE_BIT |
				     SC16IS7XX_EFCR_TXDISABLE_BIT);
		/* Initialize kthread work structs */
		kthread_init_work(&s->p[i].tx_work, sc16is7xx_tx_proc);
		kthread_init_work(&s->p[i].reg_work, sc16is7xx_reg_proc);
		/* Register port */
		uart_add_one_port(&sc16is7xx_uart, &s->p[i].port);

		/* Enable EFR */
		sc16is7xx_port_write(&s->p[i].port, SC16IS7XX_LCR_REG,
				     SC16IS7XX_LCR_CONF_MODE_B);

		regcache_cache_bypass(s->regmap, true);

		/* Enable write access to enhanced features */
		sc16is7xx_port_write(&s->p[i].port, SC16IS7XX_EFR_REG,
				     SC16IS7XX_EFR_ENABLE_BIT);

		regcache_cache_bypass(s->regmap, false);

		/* Restore access to general registers */
		sc16is7xx_port_write(&s->p[i].port, SC16IS7XX_LCR_REG, 0x00);

		/* Go to suspend mode */
		sc16is7xx_power(&s->p[i].port, 0);
	}

	/* Setup interrupt */
	ret = devm_request_irq(dev, irq, sc16is7xx_irq,
			       flags, dev_name(dev), s);
	if (!ret)
		return 0;

out_ports:
	for (i--; i >= 0; i--) {
		uart_remove_one_port(&sc16is7xx_uart, &s->p[i].port);
		clear_bit(s->p[i].port.line, &sc16is7xx_lines);
	}

#ifdef CONFIG_GPIOLIB
	if (devtype->nr_gpio)
		gpiochip_remove(&s->gpio);

out_thread:
#endif
	kthread_stop(s->kworker_task);

out_clk:
	if (!IS_ERR(s->clk))
		clk_disable_unprepare(s->clk);

	return ret;
}