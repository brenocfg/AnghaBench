#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct pm80x_rtc_pdata {int /*<<< orphan*/  rtc_wakeup; } ;
struct pm80x_rtc_info {scalar_t__ irq; TYPE_2__* rtc_dev; int /*<<< orphan*/  map; TYPE_4__* dev; struct pm80x_chip* chip; } ;
struct pm80x_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct TYPE_14__ {struct device_node* of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_4__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/ * platform_data; } ;
struct TYPE_13__ {TYPE_1__ dev; int /*<<< orphan*/  range_max; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  PM800_RTC1_USE_XO ; 
 int /*<<< orphan*/  PM800_RTC_CONTROL ; 
 int PTR_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  U32_MAX ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 struct pm80x_chip* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct pm80x_rtc_pdata* dev_get_platdata (TYPE_4__*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_4__*,struct pm80x_rtc_info*) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_4__*,int) ; 
 void* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* devm_rtc_allocate_device (TYPE_4__*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm80x_free_irq (struct pm80x_chip*,scalar_t__,struct pm80x_rtc_info*) ; 
 int pm80x_request_irq (struct pm80x_chip*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct pm80x_rtc_info*) ; 
 int /*<<< orphan*/  pm80x_rtc_ops ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtc_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  rtc_update_handler ; 

__attribute__((used)) static int pm80x_rtc_probe(struct platform_device *pdev)
{
	struct pm80x_chip *chip = dev_get_drvdata(pdev->dev.parent);
	struct pm80x_rtc_pdata *pdata = dev_get_platdata(&pdev->dev);
	struct pm80x_rtc_info *info;
	struct device_node *node = pdev->dev.of_node;
	int ret;

	if (!pdata && !node) {
		dev_err(&pdev->dev,
			"pm80x-rtc requires platform data or of_node\n");
		return -EINVAL;
	}

	if (!pdata) {
		pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
		if (!pdata) {
			dev_err(&pdev->dev, "failed to allocate memory\n");
			return -ENOMEM;
		}
	}

	info =
	    devm_kzalloc(&pdev->dev, sizeof(struct pm80x_rtc_info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;
	info->irq = platform_get_irq(pdev, 0);
	if (info->irq < 0) {
		ret = -EINVAL;
		goto out;
	}

	info->chip = chip;
	info->map = chip->regmap;
	if (!info->map) {
		dev_err(&pdev->dev, "no regmap!\n");
		ret = -EINVAL;
		goto out;
	}

	info->dev = &pdev->dev;
	dev_set_drvdata(&pdev->dev, info);

	info->rtc_dev = devm_rtc_allocate_device(&pdev->dev);
	if (IS_ERR(info->rtc_dev))
		return PTR_ERR(info->rtc_dev);

	ret = pm80x_request_irq(chip, info->irq, rtc_update_handler,
				IRQF_ONESHOT, "rtc", info);
	if (ret < 0) {
		dev_err(chip->dev, "Failed to request IRQ: #%d: %d\n",
			info->irq, ret);
		goto out;
	}

	info->rtc_dev->ops = &pm80x_rtc_ops;
	info->rtc_dev->range_max = U32_MAX;

	ret = rtc_register_device(info->rtc_dev);
	if (ret)
		goto out_rtc;

	/*
	 * enable internal XO instead of internal 3.25MHz clock since it can
	 * free running in PMIC power-down state.
	 */
	regmap_update_bits(info->map, PM800_RTC_CONTROL, PM800_RTC1_USE_XO,
			   PM800_RTC1_USE_XO);

	/* remember whether this power up is caused by PMIC RTC or not */
	info->rtc_dev->dev.platform_data = &pdata->rtc_wakeup;

	device_init_wakeup(&pdev->dev, 1);

	return 0;
out_rtc:
	pm80x_free_irq(chip, info->irq, info);
out:
	return ret;
}