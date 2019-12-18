#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct wm831x_pdata {int wm831x_num; int /*<<< orphan*/ * ldo; } ;
struct TYPE_9__ {int id; int n_voltages; int enable_mask; int /*<<< orphan*/  n_linear_ranges; int /*<<< orphan*/  linear_ranges; int /*<<< orphan*/  bypass_mask; scalar_t__ bypass_reg; int /*<<< orphan*/  enable_reg; int /*<<< orphan*/  vsel_mask; scalar_t__ vsel_reg; int /*<<< orphan*/  owner; int /*<<< orphan*/ * ops; int /*<<< orphan*/  type; int /*<<< orphan*/  supply_name; int /*<<< orphan*/  name; } ;
struct wm831x_ldo {int /*<<< orphan*/  name; int /*<<< orphan*/  regulator; TYPE_3__ desc; scalar_t__ base; int /*<<< orphan*/  supply_name; struct wm831x* wm831x; } ;
struct wm831x {TYPE_1__* dev; int /*<<< orphan*/  regmap; } ;
struct resource {scalar_t__ start; } ;
struct regulator_config {int /*<<< orphan*/  regmap; struct wm831x_ldo* driver_data; int /*<<< orphan*/  init_data; int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct platform_device {int id; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_REG ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGULATOR_VOLTAGE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  WM831X_LDO1_ON_VSEL_MASK ; 
 int /*<<< orphan*/  WM831X_LDO1_SWI ; 
 int /*<<< orphan*/  WM831X_LDO_ENABLE ; 
 scalar_t__ WM831X_LDO_ON_CONTROL ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct wm831x* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct wm831x_pdata* dev_get_platdata (TYPE_1__*) ; 
 struct wm831x_ldo* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_register (TYPE_1__*,TYPE_3__*,struct regulator_config*) ; 
 int devm_request_threaded_irq (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct wm831x_ldo*) ; 
 int /*<<< orphan*/  platform_get_irq_byname (struct platform_device*,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct wm831x_ldo*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  wm831x_gp_ldo_ops ; 
 int /*<<< orphan*/  wm831x_gp_ldo_ranges ; 
 int wm831x_irq (struct wm831x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm831x_ldo_uv_irq ; 

__attribute__((used)) static int wm831x_gp_ldo_probe(struct platform_device *pdev)
{
	struct wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	struct wm831x_pdata *pdata = dev_get_platdata(wm831x->dev);
	struct regulator_config config = { };
	int id;
	struct wm831x_ldo *ldo;
	struct resource *res;
	int ret, irq;

	if (pdata && pdata->wm831x_num)
		id = (pdata->wm831x_num * 10) + 1;
	else
		id = 0;
	id = pdev->id - id;

	dev_dbg(&pdev->dev, "Probing LDO%d\n", id + 1);

	ldo = devm_kzalloc(&pdev->dev, sizeof(struct wm831x_ldo), GFP_KERNEL);
	if (!ldo)
		return -ENOMEM;

	ldo->wm831x = wm831x;

	res = platform_get_resource(pdev, IORESOURCE_REG, 0);
	if (res == NULL) {
		dev_err(&pdev->dev, "No REG resource\n");
		ret = -EINVAL;
		goto err;
	}
	ldo->base = res->start;

	snprintf(ldo->name, sizeof(ldo->name), "LDO%d", id + 1);
	ldo->desc.name = ldo->name;

	snprintf(ldo->supply_name, sizeof(ldo->supply_name),
		 "LDO%dVDD", id + 1);
	ldo->desc.supply_name = ldo->supply_name;

	ldo->desc.id = id;
	ldo->desc.type = REGULATOR_VOLTAGE;
	ldo->desc.n_voltages = 32;
	ldo->desc.ops = &wm831x_gp_ldo_ops;
	ldo->desc.owner = THIS_MODULE;
	ldo->desc.vsel_reg = ldo->base + WM831X_LDO_ON_CONTROL;
	ldo->desc.vsel_mask = WM831X_LDO1_ON_VSEL_MASK;
	ldo->desc.enable_reg = WM831X_LDO_ENABLE;
	ldo->desc.enable_mask = 1 << id;
	ldo->desc.bypass_reg = ldo->base;
	ldo->desc.bypass_mask = WM831X_LDO1_SWI;
	ldo->desc.linear_ranges = wm831x_gp_ldo_ranges;
	ldo->desc.n_linear_ranges = ARRAY_SIZE(wm831x_gp_ldo_ranges);

	config.dev = pdev->dev.parent;
	if (pdata)
		config.init_data = pdata->ldo[id];
	config.driver_data = ldo;
	config.regmap = wm831x->regmap;

	ldo->regulator = devm_regulator_register(&pdev->dev, &ldo->desc,
						 &config);
	if (IS_ERR(ldo->regulator)) {
		ret = PTR_ERR(ldo->regulator);
		dev_err(wm831x->dev, "Failed to register LDO%d: %d\n",
			id + 1, ret);
		goto err;
	}

	irq = wm831x_irq(wm831x, platform_get_irq_byname(pdev, "UV"));
	ret = devm_request_threaded_irq(&pdev->dev, irq, NULL,
					wm831x_ldo_uv_irq,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					ldo->name,
					ldo);
	if (ret != 0) {
		dev_err(&pdev->dev, "Failed to request UV IRQ %d: %d\n",
			irq, ret);
		goto err;
	}

	platform_set_drvdata(pdev, ldo);

	return 0;

err:
	return ret;
}