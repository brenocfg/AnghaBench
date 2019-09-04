#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct da9055_hwmon {TYPE_1__* da9055; int /*<<< orphan*/  done; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  hwmon_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_HIGH ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 int /*<<< orphan*/  da9055_auxadc_irq ; 
 int /*<<< orphan*/  da9055_groups ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,char*,struct da9055_hwmon*,int /*<<< orphan*/ ) ; 
 struct da9055_hwmon* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct da9055_hwmon*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 

__attribute__((used)) static int da9055_hwmon_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct da9055_hwmon *hwmon;
	struct device *hwmon_dev;
	int hwmon_irq, ret;

	hwmon = devm_kzalloc(dev, sizeof(struct da9055_hwmon), GFP_KERNEL);
	if (!hwmon)
		return -ENOMEM;

	mutex_init(&hwmon->hwmon_lock);
	mutex_init(&hwmon->irq_lock);

	init_completion(&hwmon->done);
	hwmon->da9055 = dev_get_drvdata(pdev->dev.parent);

	hwmon_irq = platform_get_irq_byname(pdev, "HWMON");
	if (hwmon_irq < 0)
		return hwmon_irq;

	ret = devm_request_threaded_irq(&pdev->dev, hwmon_irq,
					NULL, da9055_auxadc_irq,
					IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					"adc-irq", hwmon);
	if (ret != 0) {
		dev_err(hwmon->da9055->dev, "DA9055 ADC IRQ failed ret=%d\n",
			ret);
		return ret;
	}

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, "da9055",
							   hwmon,
							   da9055_groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}