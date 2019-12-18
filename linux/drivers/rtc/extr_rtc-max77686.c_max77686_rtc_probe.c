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
struct platform_device_id {int /*<<< orphan*/  name; scalar_t__ driver_data; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct max77686_rtc_info {int /*<<< orphan*/  rtc_irq_data; int /*<<< orphan*/  rtc_irq; int /*<<< orphan*/  virq; int /*<<< orphan*/  rtc_dev; struct max77686_rtc_driver_data const* drv_data; int /*<<< orphan*/ * dev; int /*<<< orphan*/  lock; } ;
struct max77686_rtc_driver_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX77686_RTCIRQ_RTCA1 ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 struct max77686_rtc_info* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_rtc_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int max77686_init_rtc_regmap (struct max77686_rtc_info*) ; 
 int /*<<< orphan*/  max77686_rtc_alarm_irq ; 
 int max77686_rtc_init_reg (struct max77686_rtc_info*) ; 
 int /*<<< orphan*/  max77686_rtc_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct platform_device_id* platform_get_device_id (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct max77686_rtc_info*) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_irq_get_virq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct max77686_rtc_info*) ; 

__attribute__((used)) static int max77686_rtc_probe(struct platform_device *pdev)
{
	struct max77686_rtc_info *info;
	const struct platform_device_id *id = platform_get_device_id(pdev);
	int ret;

	info = devm_kzalloc(&pdev->dev, sizeof(struct max77686_rtc_info),
			    GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	mutex_init(&info->lock);
	info->dev = &pdev->dev;
	info->drv_data = (const struct max77686_rtc_driver_data *)
		id->driver_data;

	ret = max77686_init_rtc_regmap(info);
	if (ret < 0)
		return ret;

	platform_set_drvdata(pdev, info);

	ret = max77686_rtc_init_reg(info);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to initialize RTC reg:%d\n", ret);
		goto err_rtc;
	}

	device_init_wakeup(&pdev->dev, 1);

	info->rtc_dev = devm_rtc_device_register(&pdev->dev, id->name,
					&max77686_rtc_ops, THIS_MODULE);

	if (IS_ERR(info->rtc_dev)) {
		ret = PTR_ERR(info->rtc_dev);
		dev_err(&pdev->dev, "Failed to register RTC device: %d\n", ret);
		if (ret == 0)
			ret = -EINVAL;
		goto err_rtc;
	}

	info->virq = regmap_irq_get_virq(info->rtc_irq_data,
					 MAX77686_RTCIRQ_RTCA1);
	if (info->virq <= 0) {
		ret = -ENXIO;
		goto err_rtc;
	}

	ret = request_threaded_irq(info->virq, NULL, max77686_rtc_alarm_irq, 0,
				   "rtc-alarm1", info);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to request alarm IRQ: %d: %d\n",
			info->virq, ret);
		goto err_rtc;
	}

	return 0;

err_rtc:
	regmap_del_irq_chip(info->rtc_irq, info->rtc_irq_data);

	return ret;
}