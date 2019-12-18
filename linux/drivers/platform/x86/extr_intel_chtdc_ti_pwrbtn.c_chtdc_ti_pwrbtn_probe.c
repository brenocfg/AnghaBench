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
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct intel_soc_pmic {int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {char* phys; TYPE_1__ id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  KEY_POWER ; 
 int /*<<< orphan*/  chtdc_ti_pwrbtn_interrupt ; 
 struct intel_soc_pmic* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_set_wake_irq (struct device*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_init_wakeup (struct device*,int) ; 
 struct input_dev* devm_input_allocate_device (struct device*) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chtdc_ti_pwrbtn_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct intel_soc_pmic *pmic = dev_get_drvdata(dev->parent);
	struct input_dev *input;
	int irq, err;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;
	input = devm_input_allocate_device(dev);
	if (!input)
		return -ENOMEM;
	input->name = pdev->name;
	input->phys = "power-button/input0";
	input->id.bustype = BUS_HOST;
	input_set_capability(input, EV_KEY, KEY_POWER);
	err = input_register_device(input);
	if (err)
		return err;

	dev_set_drvdata(dev, pmic->regmap);

	err = devm_request_threaded_irq(dev, irq, NULL,
					chtdc_ti_pwrbtn_interrupt,
					0, KBUILD_MODNAME, input);
	if (err)
		return err;

	device_init_wakeup(dev, true);
	dev_pm_set_wake_irq(dev, irq);
	return 0;
}