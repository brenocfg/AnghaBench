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
struct sun6i_rtc_dev {scalar_t__ irq; int /*<<< orphan*/  rtc; int /*<<< orphan*/  losc; scalar_t__ base; int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SUN6I_ALARM_CONFIG ; 
 scalar_t__ SUN6I_ALRM1_EN ; 
 scalar_t__ SUN6I_ALRM1_IRQ_EN ; 
 scalar_t__ SUN6I_ALRM1_IRQ_STA ; 
 int /*<<< orphan*/  SUN6I_ALRM1_IRQ_STA_WEEK_IRQ_PEND ; 
 scalar_t__ SUN6I_ALRM_COUNTER ; 
 scalar_t__ SUN6I_ALRM_EN ; 
 scalar_t__ SUN6I_ALRM_IRQ_EN ; 
 scalar_t__ SUN6I_ALRM_IRQ_STA ; 
 int /*<<< orphan*/  SUN6I_ALRM_IRQ_STA_CNT_IRQ_PEND ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sun6i_rtc_dev*) ; 
 int /*<<< orphan*/  devm_rtc_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sun6i_rtc_dev*) ; 
 struct sun6i_rtc_dev* sun6i_rtc ; 
 int /*<<< orphan*/  sun6i_rtc_alarmirq ; 
 int /*<<< orphan*/  sun6i_rtc_ops ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sun6i_rtc_probe(struct platform_device *pdev)
{
	struct sun6i_rtc_dev *chip = sun6i_rtc;
	int ret;

	if (!chip)
		return -ENODEV;

	platform_set_drvdata(pdev, chip);
	chip->dev = &pdev->dev;

	chip->irq = platform_get_irq(pdev, 0);
	if (chip->irq < 0)
		return chip->irq;

	ret = devm_request_irq(&pdev->dev, chip->irq, sun6i_rtc_alarmirq,
			       0, dev_name(&pdev->dev), chip);
	if (ret) {
		dev_err(&pdev->dev, "Could not request IRQ\n");
		return ret;
	}

	/* clear the alarm counter value */
	writel(0, chip->base + SUN6I_ALRM_COUNTER);

	/* disable counter alarm */
	writel(0, chip->base + SUN6I_ALRM_EN);

	/* disable counter alarm interrupt */
	writel(0, chip->base + SUN6I_ALRM_IRQ_EN);

	/* disable week alarm */
	writel(0, chip->base + SUN6I_ALRM1_EN);

	/* disable week alarm interrupt */
	writel(0, chip->base + SUN6I_ALRM1_IRQ_EN);

	/* clear counter alarm pending interrupts */
	writel(SUN6I_ALRM_IRQ_STA_CNT_IRQ_PEND,
	       chip->base + SUN6I_ALRM_IRQ_STA);

	/* clear week alarm pending interrupts */
	writel(SUN6I_ALRM1_IRQ_STA_WEEK_IRQ_PEND,
	       chip->base + SUN6I_ALRM1_IRQ_STA);

	/* disable alarm wakeup */
	writel(0, chip->base + SUN6I_ALARM_CONFIG);

	clk_prepare_enable(chip->losc);

	device_init_wakeup(&pdev->dev, 1);

	chip->rtc = devm_rtc_device_register(&pdev->dev, "rtc-sun6i",
					     &sun6i_rtc_ops, THIS_MODULE);
	if (IS_ERR(chip->rtc)) {
		dev_err(&pdev->dev, "unable to register device\n");
		return PTR_ERR(chip->rtc);
	}

	dev_info(&pdev->dev, "RTC enabled\n");

	return 0;
}