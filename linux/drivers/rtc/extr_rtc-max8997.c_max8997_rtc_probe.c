#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct max8997_rtc_info {int virq; int /*<<< orphan*/  rtc_dev; int /*<<< orphan*/  rtc; struct max8997_dev* max8997; TYPE_1__* dev; int /*<<< orphan*/  lock; } ;
struct max8997_dev {int /*<<< orphan*/  irq_domain; int /*<<< orphan*/  rtc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX8997_PMICIRQ_RTCA1 ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct max8997_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_1__*,int) ; 
 struct max8997_rtc_info* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct max8997_rtc_info*) ; 
 int /*<<< orphan*/  devm_rtc_device_register (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int irq_create_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max8997_rtc_alarm_irq ; 
 int /*<<< orphan*/  max8997_rtc_enable_smpl (struct max8997_rtc_info*,int) ; 
 int /*<<< orphan*/  max8997_rtc_enable_wtsr (struct max8997_rtc_info*,int) ; 
 int max8997_rtc_init_reg (struct max8997_rtc_info*) ; 
 int /*<<< orphan*/  max8997_rtc_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct max8997_rtc_info*) ; 

__attribute__((used)) static int max8997_rtc_probe(struct platform_device *pdev)
{
	struct max8997_dev *max8997 = dev_get_drvdata(pdev->dev.parent);
	struct max8997_rtc_info *info;
	int ret, virq;

	info = devm_kzalloc(&pdev->dev, sizeof(struct max8997_rtc_info),
			GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	mutex_init(&info->lock);
	info->dev = &pdev->dev;
	info->max8997 = max8997;
	info->rtc = max8997->rtc;

	platform_set_drvdata(pdev, info);

	ret = max8997_rtc_init_reg(info);

	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to initialize RTC reg:%d\n", ret);
		return ret;
	}

	max8997_rtc_enable_wtsr(info, true);
	max8997_rtc_enable_smpl(info, true);

	device_init_wakeup(&pdev->dev, 1);

	info->rtc_dev = devm_rtc_device_register(&pdev->dev, "max8997-rtc",
					&max8997_rtc_ops, THIS_MODULE);

	if (IS_ERR(info->rtc_dev)) {
		ret = PTR_ERR(info->rtc_dev);
		dev_err(&pdev->dev, "Failed to register RTC device: %d\n", ret);
		return ret;
	}

	virq = irq_create_mapping(max8997->irq_domain, MAX8997_PMICIRQ_RTCA1);
	if (!virq) {
		dev_err(&pdev->dev, "Failed to create mapping alarm IRQ\n");
		ret = -ENXIO;
		goto err_out;
	}
	info->virq = virq;

	ret = devm_request_threaded_irq(&pdev->dev, virq, NULL,
				max8997_rtc_alarm_irq, 0,
				"rtc-alarm0", info);
	if (ret < 0)
		dev_err(&pdev->dev, "Failed to request alarm IRQ: %d: %d\n",
			info->virq, ret);

err_out:
	return ret;
}