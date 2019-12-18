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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct db8500_thermal_zone {int /*<<< orphan*/  tz; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_NO_SUSPEND ; 
 int IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRCMU_DEFAULT_LOW_TEMP ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THERMAL_TREND_STABLE ; 
 int /*<<< orphan*/ * db8500_thermal_points ; 
 int /*<<< orphan*/  db8500_thermal_update_config (struct db8500_thermal_zone*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct db8500_thermal_zone* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct db8500_thermal_zone*) ; 
 int /*<<< orphan*/  devm_thermal_zone_of_sensor_register (struct device*,int /*<<< orphan*/ ,struct db8500_thermal_zone*,int /*<<< orphan*/ *) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct db8500_thermal_zone*) ; 
 int /*<<< orphan*/  prcmu_high_irq_handler ; 
 int /*<<< orphan*/  prcmu_low_irq_handler ; 
 int /*<<< orphan*/  thdev_ops ; 

__attribute__((used)) static int db8500_thermal_probe(struct platform_device *pdev)
{
	struct db8500_thermal_zone *th = NULL;
	struct device *dev = &pdev->dev;
	int low_irq, high_irq, ret = 0;

	th = devm_kzalloc(dev, sizeof(*th), GFP_KERNEL);
	if (!th)
		return -ENOMEM;

	low_irq = platform_get_irq_byname(pdev, "IRQ_HOTMON_LOW");
	if (low_irq < 0) {
		dev_err(dev, "Get IRQ_HOTMON_LOW failed\n");
		return low_irq;
	}

	ret = devm_request_threaded_irq(dev, low_irq, NULL,
		prcmu_low_irq_handler, IRQF_NO_SUSPEND | IRQF_ONESHOT,
		"dbx500_temp_low", th);
	if (ret < 0) {
		dev_err(dev, "failed to allocate temp low irq\n");
		return ret;
	}

	high_irq = platform_get_irq_byname(pdev, "IRQ_HOTMON_HIGH");
	if (high_irq < 0) {
		dev_err(dev, "Get IRQ_HOTMON_HIGH failed\n");
		return high_irq;
	}

	ret = devm_request_threaded_irq(dev, high_irq, NULL,
		prcmu_high_irq_handler, IRQF_NO_SUSPEND | IRQF_ONESHOT,
		"dbx500_temp_high", th);
	if (ret < 0) {
		dev_err(dev, "failed to allocate temp high irq\n");
		return ret;
	}

	/* register of thermal sensor and get info from DT */
	th->tz = devm_thermal_zone_of_sensor_register(dev, 0, th, &thdev_ops);
	if (IS_ERR(th->tz)) {
		dev_err(dev, "register thermal zone sensor failed\n");
		return PTR_ERR(th->tz);
	}
	dev_info(dev, "thermal zone sensor registered\n");

	/* Start measuring at the lowest point */
	db8500_thermal_update_config(th, 0, THERMAL_TREND_STABLE,
				     PRCMU_DEFAULT_LOW_TEMP,
				     db8500_thermal_points[0]);

	platform_set_drvdata(pdev, th);

	return 0;
}