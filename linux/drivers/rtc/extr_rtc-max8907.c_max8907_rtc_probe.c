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
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct max8907_rtc {int irq; int /*<<< orphan*/  rtc_dev; int /*<<< orphan*/  regmap; struct max8907* max8907; } ;
struct max8907 {int /*<<< orphan*/  irqc_rtc; int /*<<< orphan*/  regmap_rtc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX8907_IRQ_RTC_ALARM0 ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int,...) ; 
 struct max8907* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct max8907_rtc* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct max8907_rtc*) ; 
 int /*<<< orphan*/  devm_rtc_device_register (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max8907_irq_handler ; 
 int /*<<< orphan*/  max8907_rtc_ops ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct max8907_rtc*) ; 
 int regmap_irq_get_virq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max8907_rtc_probe(struct platform_device *pdev)
{
	struct max8907 *max8907 = dev_get_drvdata(pdev->dev.parent);
	struct max8907_rtc *rtc;
	int ret;

	rtc = devm_kzalloc(&pdev->dev, sizeof(*rtc), GFP_KERNEL);
	if (!rtc)
		return -ENOMEM;
	platform_set_drvdata(pdev, rtc);

	rtc->max8907 = max8907;
	rtc->regmap = max8907->regmap_rtc;

	rtc->rtc_dev = devm_rtc_device_register(&pdev->dev, "max8907-rtc",
					&max8907_rtc_ops, THIS_MODULE);
	if (IS_ERR(rtc->rtc_dev)) {
		ret = PTR_ERR(rtc->rtc_dev);
		dev_err(&pdev->dev, "Failed to register RTC device: %d\n", ret);
		return ret;
	}

	rtc->irq = regmap_irq_get_virq(max8907->irqc_rtc,
				       MAX8907_IRQ_RTC_ALARM0);
	if (rtc->irq < 0)
		return rtc->irq;

	ret = devm_request_threaded_irq(&pdev->dev, rtc->irq, NULL,
				max8907_irq_handler,
				IRQF_ONESHOT, "max8907-alarm0", rtc);
	if (ret < 0)
		dev_err(&pdev->dev, "Failed to request IRQ%d: %d\n",
			rtc->irq, ret);

	return ret;
}