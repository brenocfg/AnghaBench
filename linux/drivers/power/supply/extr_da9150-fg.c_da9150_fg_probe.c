#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct device {struct da9150_fg_pdata* platform_data; scalar_t__ of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct da9150_fg_pdata {int warn_soc_lvl; int crit_soc_lvl; scalar_t__ update_interval; } ;
struct da9150_fg {int warn_soc; int crit_soc; int /*<<< orphan*/  work; scalar_t__ interval; int /*<<< orphan*/  battery; int /*<<< orphan*/  io_lock; struct device* dev; struct da9150* da9150; } ;
struct da9150 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9150_CORE2WIRE_CTRL_A ; 
 int /*<<< orphan*/  DA9150_FG_QIF_EN_MASK ; 
 int /*<<< orphan*/  DA9150_QIF_FW_MAIN_VER ; 
 int /*<<< orphan*/  DA9150_QIF_FW_MAIN_VER_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 struct da9150_fg_pdata* da9150_fg_dt_pdata (struct device*) ; 
 int /*<<< orphan*/  da9150_fg_irq ; 
 int da9150_fg_read_attr (struct da9150_fg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da9150_fg_soc_event_config (struct da9150_fg*) ; 
 int /*<<< orphan*/  da9150_fg_work ; 
 int /*<<< orphan*/  da9150_set_bits (struct da9150*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 struct da9150* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct da9150_fg_pdata* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 struct da9150_fg* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_power_supply_register (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct da9150_fg*) ; 
 int /*<<< orphan*/  fg_desc ; 
 int /*<<< orphan*/  msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct da9150_fg*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9150_fg_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct da9150 *da9150 = dev_get_drvdata(dev->parent);
	struct da9150_fg_pdata *fg_pdata = dev_get_platdata(dev);
	struct da9150_fg *fg;
	int ver, irq, ret = 0;

	fg = devm_kzalloc(dev, sizeof(*fg), GFP_KERNEL);
	if (fg == NULL)
		return -ENOMEM;

	platform_set_drvdata(pdev, fg);
	fg->da9150 = da9150;
	fg->dev = dev;

	mutex_init(&fg->io_lock);

	/* Enable QIF */
	da9150_set_bits(da9150, DA9150_CORE2WIRE_CTRL_A, DA9150_FG_QIF_EN_MASK,
			DA9150_FG_QIF_EN_MASK);

	fg->battery = devm_power_supply_register(dev, &fg_desc, NULL);
	if (IS_ERR(fg->battery)) {
		ret = PTR_ERR(fg->battery);
		return ret;
	}

	ver = da9150_fg_read_attr(fg, DA9150_QIF_FW_MAIN_VER,
				  DA9150_QIF_FW_MAIN_VER_SIZE);
	dev_info(dev, "Version: 0x%x\n", ver);

	/* Handle DT data if provided */
	if (dev->of_node) {
		fg_pdata = da9150_fg_dt_pdata(dev);
		dev->platform_data = fg_pdata;
	}

	/* Handle any pdata provided */
	if (fg_pdata) {
		fg->interval = fg_pdata->update_interval;

		if (fg_pdata->warn_soc_lvl > 100)
			dev_warn(dev, "Invalid SOC warning level provided, Ignoring");
		else
			fg->warn_soc = fg_pdata->warn_soc_lvl;

		if ((fg_pdata->crit_soc_lvl > 100) ||
		    (fg_pdata->crit_soc_lvl >= fg_pdata->warn_soc_lvl))
			dev_warn(dev, "Invalid SOC critical level provided, Ignoring");
		else
			fg->crit_soc = fg_pdata->crit_soc_lvl;


	}

	/* Configure initial SOC level events */
	da9150_fg_soc_event_config(fg);

	/*
	 * If an interval period has been provided then setup repeating
	 * work for reporting data updates.
	 */
	if (fg->interval) {
		INIT_DELAYED_WORK(&fg->work, da9150_fg_work);
		schedule_delayed_work(&fg->work,
				      msecs_to_jiffies(fg->interval));
	}

	/* Register IRQ */
	irq = platform_get_irq_byname(pdev, "FG");
	if (irq < 0) {
		dev_err(dev, "Failed to get IRQ FG: %d\n", irq);
		ret = irq;
		goto irq_fail;
	}

	ret = devm_request_threaded_irq(dev, irq, NULL, da9150_fg_irq,
					IRQF_ONESHOT, "FG", fg);
	if (ret) {
		dev_err(dev, "Failed to request IRQ %d: %d\n", irq, ret);
		goto irq_fail;
	}

	return 0;

irq_fail:
	if (fg->interval)
		cancel_delayed_work(&fg->work);

	return ret;
}