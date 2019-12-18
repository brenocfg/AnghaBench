#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ pretimeout; int /*<<< orphan*/  timeout; int /*<<< orphan*/  max_timeout; int /*<<< orphan*/  min_timeout; struct device* parent; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct pm8916_wdt {TYPE_1__ wdev; scalar_t__ baseaddr; int /*<<< orphan*/  regmap; } ;
struct device {struct device* parent; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PM8916_WDT_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  PM8916_WDT_MAX_TIMEOUT ; 
 int /*<<< orphan*/  PM8916_WDT_MIN_TIMEOUT ; 
 scalar_t__ PON_PMIC_WD_RESET_S2_CTL ; 
 int /*<<< orphan*/  RESET_TYPE_HARD ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_get_regmap (struct device*,int /*<<< orphan*/ *) ; 
 int device_property_read_u32 (struct device*,char*,scalar_t__*) ; 
 struct pm8916_wdt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct pm8916_wdt*) ; 
 int devm_watchdog_register_device (struct device*,TYPE_1__*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8916_wdt_configure_timers (TYPE_1__*) ; 
 int /*<<< orphan*/  pm8916_wdt_ident ; 
 int /*<<< orphan*/  pm8916_wdt_isr ; 
 int /*<<< orphan*/  pm8916_wdt_ops ; 
 int /*<<< orphan*/  pm8916_wdt_pt_ident ; 
 int regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct pm8916_wdt*) ; 

__attribute__((used)) static int pm8916_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct pm8916_wdt *wdt;
	struct device *parent;
	int err, irq;

	wdt = devm_kzalloc(dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	parent = dev->parent;

	/*
	 * The pm8916-pon-wdt is a child of the pon device, which is a child
	 * of the pm8916 mfd device. We want access to the pm8916 registers.
	 * Retrieve regmap from pm8916 (parent->parent) and base address
	 * from pm8916-pon (pon).
	 */
	wdt->regmap = dev_get_regmap(parent->parent, NULL);
	if (!wdt->regmap) {
		dev_err(dev, "failed to locate regmap\n");
		return -ENODEV;
	}

	err = device_property_read_u32(parent, "reg", &wdt->baseaddr);
	if (err) {
		dev_err(dev, "failed to get pm8916-pon address\n");
		return err;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq > 0) {
		err = devm_request_irq(dev, irq, pm8916_wdt_isr, 0,
				       "pm8916_wdt", wdt);
		if (err)
			return err;

		wdt->wdev.info = &pm8916_wdt_pt_ident;
	} else {
		if (irq == -EPROBE_DEFER)
			return -EPROBE_DEFER;

		wdt->wdev.info = &pm8916_wdt_ident;
	}

	/* Configure watchdog to hard-reset mode */
	err = regmap_write(wdt->regmap,
			   wdt->baseaddr + PON_PMIC_WD_RESET_S2_CTL,
			   RESET_TYPE_HARD);
	if (err) {
		dev_err(dev, "failed configure watchdog\n");
		return err;
	}

	wdt->wdev.ops = &pm8916_wdt_ops,
	wdt->wdev.parent = dev;
	wdt->wdev.min_timeout = PM8916_WDT_MIN_TIMEOUT;
	wdt->wdev.max_timeout = PM8916_WDT_MAX_TIMEOUT;
	wdt->wdev.timeout = PM8916_WDT_DEFAULT_TIMEOUT;
	wdt->wdev.pretimeout = 0;
	watchdog_set_drvdata(&wdt->wdev, wdt);

	watchdog_init_timeout(&wdt->wdev, 0, dev);
	pm8916_wdt_configure_timers(&wdt->wdev);

	return devm_watchdog_register_device(dev, &wdt->wdev);
}