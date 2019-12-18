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
struct sirfsoc_rtc_drv {int /*<<< orphan*/  irq; int /*<<< orphan*/  rtc; int /*<<< orphan*/  overflow_rtc; int /*<<< orphan*/  regmap; int /*<<< orphan*/  rtc_base; int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_ALARM0 ; 
 int /*<<< orphan*/  RTC_ALARM1 ; 
 int /*<<< orphan*/  RTC_CLOCK_SWITCH ; 
 int /*<<< orphan*/  RTC_DIV ; 
 int RTC_HZ ; 
 int /*<<< orphan*/  RTC_SW_VALUE ; 
 int SIRFSOC_RTC_CLK ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_1__*,int) ; 
 struct sirfsoc_rtc_drv* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_iobg (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int devm_request_irq (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sirfsoc_rtc_drv*) ; 
 int /*<<< orphan*/  devm_rtc_device_register (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sirfsoc_rtc_drv*) ; 
 int /*<<< orphan*/  sirfsoc_rtc_irq_handler ; 
 int /*<<< orphan*/  sirfsoc_rtc_ops ; 
 int /*<<< orphan*/  sirfsoc_rtc_readl (struct sirfsoc_rtc_drv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sirfsoc_rtc_writel (struct sirfsoc_rtc_drv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysrtc_regmap_config ; 

__attribute__((used)) static int sirfsoc_rtc_probe(struct platform_device *pdev)
{
	int err;
	unsigned long rtc_div;
	struct sirfsoc_rtc_drv *rtcdrv;
	struct device_node *np = pdev->dev.of_node;

	rtcdrv = devm_kzalloc(&pdev->dev,
		sizeof(struct sirfsoc_rtc_drv), GFP_KERNEL);
	if (rtcdrv == NULL)
		return -ENOMEM;

	spin_lock_init(&rtcdrv->lock);

	err = of_property_read_u32(np, "reg", &rtcdrv->rtc_base);
	if (err) {
		dev_err(&pdev->dev, "unable to find base address of rtc node in dtb\n");
		return err;
	}

	platform_set_drvdata(pdev, rtcdrv);

	/* Register rtc alarm as a wakeup source */
	device_init_wakeup(&pdev->dev, 1);

	rtcdrv->regmap = devm_regmap_init_iobg(&pdev->dev,
			&sysrtc_regmap_config);
	if (IS_ERR(rtcdrv->regmap)) {
		err = PTR_ERR(rtcdrv->regmap);
		dev_err(&pdev->dev, "Failed to allocate register map: %d\n",
			err);
		return err;
	}

	/*
	 * Set SYS_RTC counter in RTC_HZ HZ Units
	 * We are using 32K RTC crystal (32768 / RTC_HZ / 2) -1
	 * If 16HZ, therefore RTC_DIV = 1023;
	 */
	rtc_div = ((32768 / RTC_HZ) / 2) - 1;
	sirfsoc_rtc_writel(rtcdrv, RTC_DIV, rtc_div);

	/* 0x3 -> RTC_CLK */
	sirfsoc_rtc_writel(rtcdrv, RTC_CLOCK_SWITCH, SIRFSOC_RTC_CLK);

	/* reset SYS RTC ALARM0 */
	sirfsoc_rtc_writel(rtcdrv, RTC_ALARM0, 0x0);

	/* reset SYS RTC ALARM1 */
	sirfsoc_rtc_writel(rtcdrv, RTC_ALARM1, 0x0);

	/* Restore RTC Overflow From Register After Command Reboot */
	rtcdrv->overflow_rtc =
		sirfsoc_rtc_readl(rtcdrv, RTC_SW_VALUE);

	rtcdrv->rtc = devm_rtc_device_register(&pdev->dev, pdev->name,
			&sirfsoc_rtc_ops, THIS_MODULE);
	if (IS_ERR(rtcdrv->rtc)) {
		err = PTR_ERR(rtcdrv->rtc);
		dev_err(&pdev->dev, "can't register RTC device\n");
		return err;
	}

	rtcdrv->irq = platform_get_irq(pdev, 0);
	err = devm_request_irq(
			&pdev->dev,
			rtcdrv->irq,
			sirfsoc_rtc_irq_handler,
			IRQF_SHARED,
			pdev->name,
			rtcdrv);
	if (err) {
		dev_err(&pdev->dev, "Unable to register for the SiRF SOC RTC IRQ\n");
		return err;
	}

	return 0;
}