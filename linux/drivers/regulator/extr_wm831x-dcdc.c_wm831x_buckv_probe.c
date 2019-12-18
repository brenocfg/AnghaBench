#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct wm831x_pdata {int wm831x_num; TYPE_1__** dcdc; } ;
struct TYPE_11__ {int id; int enable_mask; void* curr_table; void* n_current_limits; int /*<<< orphan*/  csel_mask; scalar_t__ csel_reg; int /*<<< orphan*/  enable_reg; int /*<<< orphan*/  owner; int /*<<< orphan*/ * ops; void* n_linear_ranges; void* linear_ranges; scalar_t__ n_voltages; int /*<<< orphan*/  type; int /*<<< orphan*/  supply_name; int /*<<< orphan*/  name; } ;
struct wm831x_dcdc {int on_vsel; int dvs_vsel; int /*<<< orphan*/  name; int /*<<< orphan*/  regulator; TYPE_4__ desc; scalar_t__ base; int /*<<< orphan*/  supply_name; struct wm831x* wm831x; } ;
struct wm831x {TYPE_2__* dev; int /*<<< orphan*/  regmap; } ;
struct resource {scalar_t__ start; } ;
struct regulator_config {int /*<<< orphan*/  regmap; struct wm831x_dcdc* driver_data; TYPE_1__* init_data; int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  parent; } ;
struct platform_device {int id; TYPE_2__ dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  driver_data; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
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
 scalar_t__ WM831X_BUCKV_MAX_SELECTOR ; 
 int WM831X_DC1_DVS_VSEL_MASK ; 
 int /*<<< orphan*/  WM831X_DC1_HC_THR_MASK ; 
 int WM831X_DC1_ON_VSEL_MASK ; 
 scalar_t__ WM831X_DCDC_CONTROL_2 ; 
 scalar_t__ WM831X_DCDC_DVS_CONTROL ; 
 int /*<<< orphan*/  WM831X_DCDC_ENABLE ; 
 scalar_t__ WM831X_DCDC_ON_CONFIG ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 struct wm831x* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct wm831x_pdata* dev_get_platdata (TYPE_2__*) ; 
 struct wm831x_dcdc* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_register (TYPE_2__*,TYPE_4__*,struct regulator_config*) ; 
 int devm_request_threaded_irq (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct wm831x_dcdc*) ; 
 int /*<<< orphan*/  platform_get_irq_byname (struct platform_device*,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct wm831x_dcdc*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  wm831x_buckv_dvs_init (struct platform_device*,struct wm831x_dcdc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm831x_buckv_ops ; 
 void* wm831x_buckv_ranges ; 
 void* wm831x_dcdc_ilim ; 
 int /*<<< orphan*/  wm831x_dcdc_oc_irq ; 
 int /*<<< orphan*/  wm831x_dcdc_uv_irq ; 
 int wm831x_irq (struct wm831x*,int /*<<< orphan*/ ) ; 
 int wm831x_reg_read (struct wm831x*,scalar_t__) ; 

__attribute__((used)) static int wm831x_buckv_probe(struct platform_device *pdev)
{
	struct wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	struct wm831x_pdata *pdata = dev_get_platdata(wm831x->dev);
	struct regulator_config config = { };
	int id;
	struct wm831x_dcdc *dcdc;
	struct resource *res;
	int ret, irq;

	if (pdata && pdata->wm831x_num)
		id = (pdata->wm831x_num * 10) + 1;
	else
		id = 0;
	id = pdev->id - id;

	dev_dbg(&pdev->dev, "Probing DCDC%d\n", id + 1);

	dcdc = devm_kzalloc(&pdev->dev,  sizeof(struct wm831x_dcdc),
			    GFP_KERNEL);
	if (!dcdc)
		return -ENOMEM;

	dcdc->wm831x = wm831x;

	res = platform_get_resource(pdev, IORESOURCE_REG, 0);
	if (res == NULL) {
		dev_err(&pdev->dev, "No REG resource\n");
		ret = -EINVAL;
		goto err;
	}
	dcdc->base = res->start;

	snprintf(dcdc->name, sizeof(dcdc->name), "DCDC%d", id + 1);
	dcdc->desc.name = dcdc->name;

	snprintf(dcdc->supply_name, sizeof(dcdc->supply_name),
		 "DC%dVDD", id + 1);
	dcdc->desc.supply_name = dcdc->supply_name;

	dcdc->desc.id = id;
	dcdc->desc.type = REGULATOR_VOLTAGE;
	dcdc->desc.n_voltages = WM831X_BUCKV_MAX_SELECTOR + 1;
	dcdc->desc.linear_ranges = wm831x_buckv_ranges;
	dcdc->desc.n_linear_ranges = ARRAY_SIZE(wm831x_buckv_ranges);
	dcdc->desc.ops = &wm831x_buckv_ops;
	dcdc->desc.owner = THIS_MODULE;
	dcdc->desc.enable_reg = WM831X_DCDC_ENABLE;
	dcdc->desc.enable_mask = 1 << id;
	dcdc->desc.csel_reg = dcdc->base + WM831X_DCDC_CONTROL_2;
	dcdc->desc.csel_mask = WM831X_DC1_HC_THR_MASK;
	dcdc->desc.n_current_limits = ARRAY_SIZE(wm831x_dcdc_ilim);
	dcdc->desc.curr_table = wm831x_dcdc_ilim;

	ret = wm831x_reg_read(wm831x, dcdc->base + WM831X_DCDC_ON_CONFIG);
	if (ret < 0) {
		dev_err(wm831x->dev, "Failed to read ON VSEL: %d\n", ret);
		goto err;
	}
	dcdc->on_vsel = ret & WM831X_DC1_ON_VSEL_MASK;

	ret = wm831x_reg_read(wm831x, dcdc->base + WM831X_DCDC_DVS_CONTROL);
	if (ret < 0) {
		dev_err(wm831x->dev, "Failed to read DVS VSEL: %d\n", ret);
		goto err;
	}
	dcdc->dvs_vsel = ret & WM831X_DC1_DVS_VSEL_MASK;

	if (pdata && pdata->dcdc[id])
		wm831x_buckv_dvs_init(pdev, dcdc,
				      pdata->dcdc[id]->driver_data);

	config.dev = pdev->dev.parent;
	if (pdata)
		config.init_data = pdata->dcdc[id];
	config.driver_data = dcdc;
	config.regmap = wm831x->regmap;

	dcdc->regulator = devm_regulator_register(&pdev->dev, &dcdc->desc,
						  &config);
	if (IS_ERR(dcdc->regulator)) {
		ret = PTR_ERR(dcdc->regulator);
		dev_err(wm831x->dev, "Failed to register DCDC%d: %d\n",
			id + 1, ret);
		goto err;
	}

	irq = wm831x_irq(wm831x, platform_get_irq_byname(pdev, "UV"));
	ret = devm_request_threaded_irq(&pdev->dev, irq, NULL,
					wm831x_dcdc_uv_irq,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					dcdc->name, dcdc);
	if (ret != 0) {
		dev_err(&pdev->dev, "Failed to request UV IRQ %d: %d\n",
			irq, ret);
		goto err;
	}

	irq = wm831x_irq(wm831x, platform_get_irq_byname(pdev, "HC"));
	ret = devm_request_threaded_irq(&pdev->dev, irq, NULL,
					wm831x_dcdc_oc_irq,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					dcdc->name, dcdc);
	if (ret != 0) {
		dev_err(&pdev->dev, "Failed to request HC IRQ %d: %d\n",
			irq, ret);
		goto err;
	}

	platform_set_drvdata(pdev, dcdc);

	return 0;

err:
	return ret;
}