#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct intel_soc_pmic {int /*<<< orphan*/  regmap; } ;
struct TYPE_4__ {struct device* parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {char* phys; TYPE_2__ dev; TYPE_1__ id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCOVE_LVL1_PWRBTN ; 
 int /*<<< orphan*/  BCOVE_MIRQLVL1 ; 
 int /*<<< orphan*/  BCOVE_MPBIRQ ; 
 int /*<<< orphan*/  BCOVE_PBIRQ_PBTN ; 
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 int /*<<< orphan*/  KEY_POWER ; 
 struct intel_soc_pmic* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_set_wake_irq (struct device*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_init_wakeup (struct device*,int) ; 
 struct input_dev* devm_input_allocate_device (struct device*) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrfld_pwrbtn_interrupt ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mrfld_pwrbtn_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct intel_soc_pmic *pmic = dev_get_drvdata(dev->parent);
	struct input_dev *input;
	int irq, ret;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	input = devm_input_allocate_device(dev);
	if (!input)
		return -ENOMEM;
	input->name = pdev->name;
	input->phys = "power-button/input0";
	input->id.bustype = BUS_HOST;
	input->dev.parent = dev;
	input_set_capability(input, EV_KEY, KEY_POWER);
	ret = input_register_device(input);
	if (ret)
		return ret;

	dev_set_drvdata(dev, pmic->regmap);

	ret = devm_request_threaded_irq(dev, irq, NULL, mrfld_pwrbtn_interrupt,
					IRQF_ONESHOT | IRQF_SHARED, pdev->name,
					input);
	if (ret)
		return ret;

	regmap_update_bits(pmic->regmap, BCOVE_MIRQLVL1, BCOVE_LVL1_PWRBTN, 0);
	regmap_update_bits(pmic->regmap, BCOVE_MPBIRQ, BCOVE_PBIRQ_PBTN, 0);

	device_init_wakeup(dev, true);
	dev_pm_set_wake_irq(dev, irq);
	return 0;
}