#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_14__ {int /*<<< orphan*/  of_node; TYPE_3__* parent; } ;
struct TYPE_12__ {int retries; TYPE_8__ dev; struct pxa_i2c* algo_data; int /*<<< orphan*/ * algo; int /*<<< orphan*/  name; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; int /*<<< orphan*/  nr; } ;
struct pxa_i2c {int irq; int highmode_enter; scalar_t__ clk; TYPE_2__ adap; int /*<<< orphan*/  slave_addr; scalar_t__ use_pio; scalar_t__ rate; scalar_t__ high_mode; int /*<<< orphan*/  slave; int /*<<< orphan*/  iosize; int /*<<< orphan*/  iobase; scalar_t__ reg_base; scalar_t__ reg_iwcr; scalar_t__ reg_ilcr; scalar_t__ reg_isar; int /*<<< orphan*/  hs_mask; int /*<<< orphan*/  fm_mask; scalar_t__ reg_isr; scalar_t__ reg_icr; scalar_t__ reg_idbr; scalar_t__ reg_ibmr; int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; } ;
struct TYPE_13__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; int /*<<< orphan*/  id; } ;
struct i2c_pxa_platform_data {int /*<<< orphan*/  class; int /*<<< orphan*/  slave; int /*<<< orphan*/  slave_addr; } ;
typedef  enum pxa_i2c_types { ____Placeholder_pxa_i2c_types } pxa_i2c_types ;
struct TYPE_11__ {scalar_t__ iwcr; scalar_t__ ilcr; scalar_t__ isar; scalar_t__ hs; scalar_t__ fm; scalar_t__ isr; scalar_t__ icr; scalar_t__ idbr; scalar_t__ ibmr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_PXA_SLAVE_ADDR ; 
 int /*<<< orphan*/  ICR_FM ; 
 int /*<<< orphan*/  ICR_HS ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IRQF_NO_SUSPEND ; 
 int IRQF_SHARED ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int REGS_CE4100 ; 
 int REGS_PXA910 ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  clk_get_rate (scalar_t__) ; 
 int /*<<< orphan*/  clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  clk_set_rate (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int) ; 
 struct i2c_pxa_platform_data* dev_get_platdata (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_info (TYPE_8__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 scalar_t__ devm_clk_get (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct pxa_i2c* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_3__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct pxa_i2c*) ; 
 int i2c_add_numbered_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  i2c_pxa_algorithm ; 
 int /*<<< orphan*/  i2c_pxa_handler ; 
 int /*<<< orphan*/  i2c_pxa_pio_algorithm ; 
 int i2c_pxa_probe_dt (struct platform_device*,struct pxa_i2c*,int*) ; 
 int i2c_pxa_probe_pdata (struct platform_device*,struct pxa_i2c*,int*) ; 
 int /*<<< orphan*/  i2c_pxa_reset (struct pxa_i2c*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pxa_i2c*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* pxa_reg_layout ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int i2c_pxa_probe(struct platform_device *dev)
{
	struct i2c_pxa_platform_data *plat = dev_get_platdata(&dev->dev);
	enum pxa_i2c_types i2c_type;
	struct pxa_i2c *i2c;
	struct resource *res = NULL;
	int ret, irq;

	i2c = devm_kzalloc(&dev->dev, sizeof(struct pxa_i2c), GFP_KERNEL);
	if (!i2c)
		return -ENOMEM;

	res = platform_get_resource(dev, IORESOURCE_MEM, 0);
	i2c->reg_base = devm_ioremap_resource(&dev->dev, res);
	if (IS_ERR(i2c->reg_base))
		return PTR_ERR(i2c->reg_base);

	irq = platform_get_irq(dev, 0);
	if (irq < 0) {
		dev_err(&dev->dev, "no irq resource: %d\n", irq);
		return irq;
	}

	/* Default adapter num to device id; i2c_pxa_probe_dt can override. */
	i2c->adap.nr = dev->id;

	ret = i2c_pxa_probe_dt(dev, i2c, &i2c_type);
	if (ret > 0)
		ret = i2c_pxa_probe_pdata(dev, i2c, &i2c_type);
	if (ret < 0)
		return ret;

	i2c->adap.owner   = THIS_MODULE;
	i2c->adap.retries = 5;

	spin_lock_init(&i2c->lock);
	init_waitqueue_head(&i2c->wait);

	strlcpy(i2c->adap.name, "pxa_i2c-i2c", sizeof(i2c->adap.name));

	i2c->clk = devm_clk_get(&dev->dev, NULL);
	if (IS_ERR(i2c->clk)) {
		dev_err(&dev->dev, "failed to get the clk: %ld\n", PTR_ERR(i2c->clk));
		return PTR_ERR(i2c->clk);
	}

	i2c->reg_ibmr = i2c->reg_base + pxa_reg_layout[i2c_type].ibmr;
	i2c->reg_idbr = i2c->reg_base + pxa_reg_layout[i2c_type].idbr;
	i2c->reg_icr = i2c->reg_base + pxa_reg_layout[i2c_type].icr;
	i2c->reg_isr = i2c->reg_base + pxa_reg_layout[i2c_type].isr;
	i2c->fm_mask = pxa_reg_layout[i2c_type].fm ? : ICR_FM;
	i2c->hs_mask = pxa_reg_layout[i2c_type].hs ? : ICR_HS;

	if (i2c_type != REGS_CE4100)
		i2c->reg_isar = i2c->reg_base + pxa_reg_layout[i2c_type].isar;

	if (i2c_type == REGS_PXA910) {
		i2c->reg_ilcr = i2c->reg_base + pxa_reg_layout[i2c_type].ilcr;
		i2c->reg_iwcr = i2c->reg_base + pxa_reg_layout[i2c_type].iwcr;
	}

	i2c->iobase = res->start;
	i2c->iosize = resource_size(res);

	i2c->irq = irq;

	i2c->slave_addr = I2C_PXA_SLAVE_ADDR;
	i2c->highmode_enter = false;

	if (plat) {
#ifdef CONFIG_I2C_PXA_SLAVE
		i2c->slave_addr = plat->slave_addr;
		i2c->slave = plat->slave;
#endif
		i2c->adap.class = plat->class;
	}

	if (i2c->high_mode) {
		if (i2c->rate) {
			clk_set_rate(i2c->clk, i2c->rate);
			pr_info("i2c: <%s> set rate to %ld\n",
				i2c->adap.name, clk_get_rate(i2c->clk));
		} else
			pr_warn("i2c: <%s> clock rate not set\n",
				i2c->adap.name);
	}

	clk_prepare_enable(i2c->clk);

	if (i2c->use_pio) {
		i2c->adap.algo = &i2c_pxa_pio_algorithm;
	} else {
		i2c->adap.algo = &i2c_pxa_algorithm;
		ret = devm_request_irq(&dev->dev, irq, i2c_pxa_handler,
				IRQF_SHARED | IRQF_NO_SUSPEND,
				dev_name(&dev->dev), i2c);
		if (ret) {
			dev_err(&dev->dev, "failed to request irq: %d\n", ret);
			goto ereqirq;
		}
	}

	i2c_pxa_reset(i2c);

	i2c->adap.algo_data = i2c;
	i2c->adap.dev.parent = &dev->dev;
#ifdef CONFIG_OF
	i2c->adap.dev.of_node = dev->dev.of_node;
#endif

	ret = i2c_add_numbered_adapter(&i2c->adap);
	if (ret < 0)
		goto ereqirq;

	platform_set_drvdata(dev, i2c);

#ifdef CONFIG_I2C_PXA_SLAVE
	dev_info(&i2c->adap.dev, " PXA I2C adapter, slave address %d\n",
		i2c->slave_addr);
#else
	dev_info(&i2c->adap.dev, " PXA I2C adapter\n");
#endif
	return 0;

ereqirq:
	clk_disable_unprepare(i2c->clk);
	return ret;
}