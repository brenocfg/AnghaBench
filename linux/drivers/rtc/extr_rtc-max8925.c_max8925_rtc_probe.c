#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct max8925_rtc_info {int /*<<< orphan*/  rtc_dev; int /*<<< orphan*/  irq; TYPE_1__* dev; int /*<<< orphan*/  rtc; struct max8925_chip* chip; } ;
struct max8925_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  rtc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int,...) ; 
 struct max8925_chip* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct max8925_rtc_info*) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_1__*,int) ; 
 struct max8925_rtc_info* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct max8925_rtc_info*) ; 
 int /*<<< orphan*/  devm_rtc_device_register (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max8925_rtc_ops ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct max8925_rtc_info*) ; 
 int /*<<< orphan*/  rtc_update_handler ; 

__attribute__((used)) static int max8925_rtc_probe(struct platform_device *pdev)
{
	struct max8925_chip *chip = dev_get_drvdata(pdev->dev.parent);
	struct max8925_rtc_info *info;
	int ret;

	info = devm_kzalloc(&pdev->dev, sizeof(struct max8925_rtc_info),
			    GFP_KERNEL);
	if (!info)
		return -ENOMEM;
	info->chip = chip;
	info->rtc = chip->rtc;
	info->dev = &pdev->dev;
	info->irq = platform_get_irq(pdev, 0);

	ret = devm_request_threaded_irq(&pdev->dev, info->irq, NULL,
					rtc_update_handler, IRQF_ONESHOT,
					"rtc-alarm0", info);
	if (ret < 0) {
		dev_err(chip->dev, "Failed to request IRQ: #%d: %d\n",
			info->irq, ret);
		return ret;
	}

	dev_set_drvdata(&pdev->dev, info);
	/* XXX - isn't this redundant? */
	platform_set_drvdata(pdev, info);

	device_init_wakeup(&pdev->dev, 1);

	info->rtc_dev = devm_rtc_device_register(&pdev->dev, "max8925-rtc",
					&max8925_rtc_ops, THIS_MODULE);
	ret = PTR_ERR(info->rtc_dev);
	if (IS_ERR(info->rtc_dev)) {
		dev_err(&pdev->dev, "Failed to register RTC device: %d\n", ret);
		return ret;
	}

	return 0;
}