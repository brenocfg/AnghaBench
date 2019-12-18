#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_13__ {int /*<<< orphan*/  notifier_call; } ;
struct TYPE_14__ {TYPE_3__* parent; struct device_node* of_node; } ;
struct TYPE_17__ {int retries; TYPE_1__ dev; struct rk3x_i2c* algo_data; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct rk3x_i2c {struct regmap* clk; struct regmap* pclk; TYPE_11__ clk_rate_nb; TYPE_4__ adap; TYPE_2__* soc_data; TYPE_3__* dev; struct regmap* regs; int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  t; } ;
struct resource {int dummy; } ;
struct regmap {int dummy; } ;
struct TYPE_16__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct of_device_id {TYPE_2__* data; } ;
struct device_node {int dummy; } ;
struct TYPE_15__ {scalar_t__ grf_offset; scalar_t__ calc_timings; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 unsigned long clk_get_rate (struct regmap*) ; 
 int clk_notifier_register (struct regmap*,TYPE_11__*) ; 
 int /*<<< orphan*/  clk_notifier_unregister (struct regmap*,TYPE_11__*) ; 
 int clk_prepare (struct regmap*) ; 
 int /*<<< orphan*/  clk_unprepare (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 void* devm_clk_get (TYPE_3__*,char*) ; 
 struct regmap* devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct rk3x_i2c* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rk3x_i2c*) ; 
 int i2c_add_adapter (TYPE_4__*) ; 
 int /*<<< orphan*/  i2c_parse_fw_timings (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int of_alias_get_id (struct device_node*,char*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,struct device_node*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rk3x_i2c*) ; 
 int regmap_write (struct regmap*,scalar_t__,int) ; 
 int /*<<< orphan*/  rk3x_i2c_adapt_div (struct rk3x_i2c*,unsigned long) ; 
 int /*<<< orphan*/  rk3x_i2c_algorithm ; 
 int /*<<< orphan*/  rk3x_i2c_clk_notifier_cb ; 
 int /*<<< orphan*/  rk3x_i2c_irq ; 
 int /*<<< orphan*/  rk3x_i2c_match ; 
 scalar_t__ rk3x_i2c_v0_calc_timings ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 struct regmap* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int rk3x_i2c_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	const struct of_device_id *match;
	struct rk3x_i2c *i2c;
	struct resource *mem;
	int ret = 0;
	int bus_nr;
	u32 value;
	int irq;
	unsigned long clk_rate;

	i2c = devm_kzalloc(&pdev->dev, sizeof(struct rk3x_i2c), GFP_KERNEL);
	if (!i2c)
		return -ENOMEM;

	match = of_match_node(rk3x_i2c_match, np);
	i2c->soc_data = match->data;

	/* use common interface to get I2C timing properties */
	i2c_parse_fw_timings(&pdev->dev, &i2c->t, true);

	strlcpy(i2c->adap.name, "rk3x-i2c", sizeof(i2c->adap.name));
	i2c->adap.owner = THIS_MODULE;
	i2c->adap.algo = &rk3x_i2c_algorithm;
	i2c->adap.retries = 3;
	i2c->adap.dev.of_node = np;
	i2c->adap.algo_data = i2c;
	i2c->adap.dev.parent = &pdev->dev;

	i2c->dev = &pdev->dev;

	spin_lock_init(&i2c->lock);
	init_waitqueue_head(&i2c->wait);

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	i2c->regs = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(i2c->regs))
		return PTR_ERR(i2c->regs);

	/* Try to set the I2C adapter number from dt */
	bus_nr = of_alias_get_id(np, "i2c");

	/*
	 * Switch to new interface if the SoC also offers the old one.
	 * The control bit is located in the GRF register space.
	 */
	if (i2c->soc_data->grf_offset >= 0) {
		struct regmap *grf;

		grf = syscon_regmap_lookup_by_phandle(np, "rockchip,grf");
		if (IS_ERR(grf)) {
			dev_err(&pdev->dev,
				"rk3x-i2c needs 'rockchip,grf' property\n");
			return PTR_ERR(grf);
		}

		if (bus_nr < 0) {
			dev_err(&pdev->dev, "rk3x-i2c needs i2cX alias");
			return -EINVAL;
		}

		/* 27+i: write mask, 11+i: value */
		value = BIT(27 + bus_nr) | BIT(11 + bus_nr);

		ret = regmap_write(grf, i2c->soc_data->grf_offset, value);
		if (ret != 0) {
			dev_err(i2c->dev, "Could not write to GRF: %d\n", ret);
			return ret;
		}
	}

	/* IRQ setup */
	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(&pdev->dev, "cannot find rk3x IRQ\n");
		return irq;
	}

	ret = devm_request_irq(&pdev->dev, irq, rk3x_i2c_irq,
			       0, dev_name(&pdev->dev), i2c);
	if (ret < 0) {
		dev_err(&pdev->dev, "cannot request IRQ\n");
		return ret;
	}

	platform_set_drvdata(pdev, i2c);

	if (i2c->soc_data->calc_timings == rk3x_i2c_v0_calc_timings) {
		/* Only one clock to use for bus clock and peripheral clock */
		i2c->clk = devm_clk_get(&pdev->dev, NULL);
		i2c->pclk = i2c->clk;
	} else {
		i2c->clk = devm_clk_get(&pdev->dev, "i2c");
		i2c->pclk = devm_clk_get(&pdev->dev, "pclk");
	}

	if (IS_ERR(i2c->clk)) {
		ret = PTR_ERR(i2c->clk);
		if (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Can't get bus clk: %d\n", ret);
		return ret;
	}
	if (IS_ERR(i2c->pclk)) {
		ret = PTR_ERR(i2c->pclk);
		if (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Can't get periph clk: %d\n", ret);
		return ret;
	}

	ret = clk_prepare(i2c->clk);
	if (ret < 0) {
		dev_err(&pdev->dev, "Can't prepare bus clk: %d\n", ret);
		return ret;
	}
	ret = clk_prepare(i2c->pclk);
	if (ret < 0) {
		dev_err(&pdev->dev, "Can't prepare periph clock: %d\n", ret);
		goto err_clk;
	}

	i2c->clk_rate_nb.notifier_call = rk3x_i2c_clk_notifier_cb;
	ret = clk_notifier_register(i2c->clk, &i2c->clk_rate_nb);
	if (ret != 0) {
		dev_err(&pdev->dev, "Unable to register clock notifier\n");
		goto err_pclk;
	}

	clk_rate = clk_get_rate(i2c->clk);
	rk3x_i2c_adapt_div(i2c, clk_rate);

	ret = i2c_add_adapter(&i2c->adap);
	if (ret < 0)
		goto err_clk_notifier;

	return 0;

err_clk_notifier:
	clk_notifier_unregister(i2c->clk, &i2c->clk_rate_nb);
err_pclk:
	clk_unprepare(i2c->pclk);
err_clk:
	clk_unprepare(i2c->clk);
	return ret;
}