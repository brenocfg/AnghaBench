#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct platform_device {int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct da9052_rtc {int /*<<< orphan*/  da9052; int /*<<< orphan*/  rtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9052_ALARM_Y_REG ; 
 int /*<<< orphan*/  DA9052_ALARM_Y_TICK_ON ; 
 int /*<<< orphan*/  DA9052_BBAT_CONT_REG ; 
 int /*<<< orphan*/  DA9052_IRQ_ALARM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int da9052_reg_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int da9052_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int da9052_request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct da9052_rtc*) ; 
 int /*<<< orphan*/  da9052_rtc_irq ; 
 int /*<<< orphan*/  da9052_rtc_ops ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_1__*,int) ; 
 struct da9052_rtc* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_rtc_device_register (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct da9052_rtc*) ; 
 int /*<<< orphan*/  rtc_err (struct da9052_rtc*,char*,int) ; 

__attribute__((used)) static int da9052_rtc_probe(struct platform_device *pdev)
{
	struct da9052_rtc *rtc;
	int ret;

	rtc = devm_kzalloc(&pdev->dev, sizeof(struct da9052_rtc), GFP_KERNEL);
	if (!rtc)
		return -ENOMEM;

	rtc->da9052 = dev_get_drvdata(pdev->dev.parent);
	platform_set_drvdata(pdev, rtc);

	ret = da9052_reg_write(rtc->da9052, DA9052_BBAT_CONT_REG, 0xFE);
	if (ret < 0) {
		rtc_err(rtc,
			"Failed to setup RTC battery charging: %d\n", ret);
		return ret;
	}

	ret = da9052_reg_update(rtc->da9052, DA9052_ALARM_Y_REG,
				DA9052_ALARM_Y_TICK_ON, 0);
	if (ret != 0)
		rtc_err(rtc, "Failed to disable TICKS: %d\n", ret);

	device_init_wakeup(&pdev->dev, true);
	rtc->rtc = devm_rtc_device_register(&pdev->dev, pdev->name,
				       &da9052_rtc_ops, THIS_MODULE);

	if (IS_ERR(rtc->rtc))
		return PTR_ERR(rtc->rtc);

	ret = da9052_request_irq(rtc->da9052, DA9052_IRQ_ALARM, "ALM",
				da9052_rtc_irq, rtc);
	if (ret != 0) {
		rtc_err(rtc, "irq registration failed: %d\n", ret);
		return ret;
	}

	return 0;
}