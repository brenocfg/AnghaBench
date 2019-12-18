#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ of_node; struct TYPE_16__* parent; } ;
struct TYPE_18__ {int retries; TYPE_1__ dev; int /*<<< orphan*/  nr; struct s3c24xx_i2c* algo_data; int /*<<< orphan*/  class; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct s3c24xx_i2c {int quirks; int tx_setup; int irq; TYPE_5__ adap; int /*<<< orphan*/  clk; TYPE_4__* pdata; int /*<<< orphan*/  pctrl; TYPE_1__* dev; int /*<<< orphan*/  regs; int /*<<< orphan*/  wait; int /*<<< orphan*/  sysreg; } ;
struct s3c2410_platform_i2c {int dummy; } ;
struct resource {int dummy; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_17__ {int /*<<< orphan*/  bus_num; int /*<<< orphan*/  (* cfg_gpio ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_DEPRECATED ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int QUIRK_POLL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct s3c2410_platform_i2c* dev_get_platdata (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 void* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pinctrl_get_select_default (TYPE_1__*) ; 
 int devm_request_irq (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct s3c24xx_i2c*) ; 
 int i2c_add_numbered_adapter (TYPE_5__*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,struct s3c2410_platform_i2c*,int) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct s3c24xx_i2c*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int s3c24xx_get_device_quirks (struct platform_device*) ; 
 int /*<<< orphan*/  s3c24xx_i2c_algorithm ; 
 int /*<<< orphan*/  s3c24xx_i2c_deregister_cpufreq (struct s3c24xx_i2c*) ; 
 int s3c24xx_i2c_init (struct s3c24xx_i2c*) ; 
 int /*<<< orphan*/  s3c24xx_i2c_irq ; 
 int /*<<< orphan*/  s3c24xx_i2c_parse_dt (scalar_t__,struct s3c24xx_i2c*) ; 
 scalar_t__ s3c24xx_i2c_parse_dt_gpio (struct s3c24xx_i2c*) ; 
 int s3c24xx_i2c_register_cpufreq (struct s3c24xx_i2c*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_platform_device (TYPE_1__*) ; 

__attribute__((used)) static int s3c24xx_i2c_probe(struct platform_device *pdev)
{
	struct s3c24xx_i2c *i2c;
	struct s3c2410_platform_i2c *pdata = NULL;
	struct resource *res;
	int ret;

	if (!pdev->dev.of_node) {
		pdata = dev_get_platdata(&pdev->dev);
		if (!pdata) {
			dev_err(&pdev->dev, "no platform data\n");
			return -EINVAL;
		}
	}

	i2c = devm_kzalloc(&pdev->dev, sizeof(struct s3c24xx_i2c), GFP_KERNEL);
	if (!i2c)
		return -ENOMEM;

	i2c->pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
	if (!i2c->pdata)
		return -ENOMEM;

	i2c->quirks = s3c24xx_get_device_quirks(pdev);
	i2c->sysreg = ERR_PTR(-ENOENT);
	if (pdata)
		memcpy(i2c->pdata, pdata, sizeof(*pdata));
	else
		s3c24xx_i2c_parse_dt(pdev->dev.of_node, i2c);

	strlcpy(i2c->adap.name, "s3c2410-i2c", sizeof(i2c->adap.name));
	i2c->adap.owner = THIS_MODULE;
	i2c->adap.algo = &s3c24xx_i2c_algorithm;
	i2c->adap.retries = 2;
	i2c->adap.class = I2C_CLASS_DEPRECATED;
	i2c->tx_setup = 50;

	init_waitqueue_head(&i2c->wait);

	/* find the clock and enable it */
	i2c->dev = &pdev->dev;
	i2c->clk = devm_clk_get(&pdev->dev, "i2c");
	if (IS_ERR(i2c->clk)) {
		dev_err(&pdev->dev, "cannot get clock\n");
		return -ENOENT;
	}

	dev_dbg(&pdev->dev, "clock source %p\n", i2c->clk);

	/* map the registers */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	i2c->regs = devm_ioremap_resource(&pdev->dev, res);

	if (IS_ERR(i2c->regs))
		return PTR_ERR(i2c->regs);

	dev_dbg(&pdev->dev, "registers %p (%p)\n",
		i2c->regs, res);

	/* setup info block for the i2c core */
	i2c->adap.algo_data = i2c;
	i2c->adap.dev.parent = &pdev->dev;
	i2c->pctrl = devm_pinctrl_get_select_default(i2c->dev);

	/* inititalise the i2c gpio lines */
	if (i2c->pdata->cfg_gpio)
		i2c->pdata->cfg_gpio(to_platform_device(i2c->dev));
	else if (IS_ERR(i2c->pctrl) && s3c24xx_i2c_parse_dt_gpio(i2c))
		return -EINVAL;

	/* initialise the i2c controller */
	ret = clk_prepare_enable(i2c->clk);
	if (ret) {
		dev_err(&pdev->dev, "I2C clock enable failed\n");
		return ret;
	}

	ret = s3c24xx_i2c_init(i2c);
	clk_disable(i2c->clk);
	if (ret != 0) {
		dev_err(&pdev->dev, "I2C controller init failed\n");
		clk_unprepare(i2c->clk);
		return ret;
	}

	/*
	 * find the IRQ for this unit (note, this relies on the init call to
	 * ensure no current IRQs pending
	 */
	if (!(i2c->quirks & QUIRK_POLL)) {
		i2c->irq = ret = platform_get_irq(pdev, 0);
		if (ret <= 0) {
			dev_err(&pdev->dev, "cannot find IRQ\n");
			clk_unprepare(i2c->clk);
			return ret;
		}

		ret = devm_request_irq(&pdev->dev, i2c->irq, s3c24xx_i2c_irq,
				       0, dev_name(&pdev->dev), i2c);
		if (ret != 0) {
			dev_err(&pdev->dev, "cannot claim IRQ %d\n", i2c->irq);
			clk_unprepare(i2c->clk);
			return ret;
		}
	}

	ret = s3c24xx_i2c_register_cpufreq(i2c);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to register cpufreq notifier\n");
		clk_unprepare(i2c->clk);
		return ret;
	}

	/*
	 * Note, previous versions of the driver used i2c_add_adapter()
	 * to add the bus at any number. We now pass the bus number via
	 * the platform data, so if unset it will now default to always
	 * being bus 0.
	 */
	i2c->adap.nr = i2c->pdata->bus_num;
	i2c->adap.dev.of_node = pdev->dev.of_node;

	platform_set_drvdata(pdev, i2c);

	pm_runtime_enable(&pdev->dev);

	ret = i2c_add_numbered_adapter(&i2c->adap);
	if (ret < 0) {
		pm_runtime_disable(&pdev->dev);
		s3c24xx_i2c_deregister_cpufreq(i2c);
		clk_unprepare(i2c->clk);
		return ret;
	}

	dev_info(&pdev->dev, "%s: S3C I2C adapter\n", dev_name(&i2c->adap.dev));
	return 0;
}