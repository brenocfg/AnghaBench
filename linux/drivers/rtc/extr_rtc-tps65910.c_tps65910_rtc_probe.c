#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tps65910_rtc {int irq; TYPE_1__* rtc; } ;
struct tps65910 {int /*<<< orphan*/  regmap; } ;
struct TYPE_15__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_14__ {int /*<<< orphan*/  range_max; int /*<<< orphan*/  range_min; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVCTRL_RTC_PWDN_MASK ; 
 int DEVCTRL_RTC_PWDN_SHIFT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_TRIGGER_LOW ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  RTC_TIMESTAMP_BEGIN_2000 ; 
 int /*<<< orphan*/  RTC_TIMESTAMP_END_2099 ; 
 int /*<<< orphan*/  TPS65910_DEVCTRL ; 
 int /*<<< orphan*/  TPS65910_RTC_CTRL ; 
 int /*<<< orphan*/  TPS65910_RTC_CTRL_STOP_RTC ; 
 int /*<<< orphan*/  TPS65910_RTC_STATUS ; 
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 struct tps65910* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (TYPE_3__*,int) ; 
 struct tps65910_rtc* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_1__* devm_rtc_allocate_device (TYPE_3__*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tps65910_rtc*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtc_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  tps65910_rtc_interrupt ; 
 int /*<<< orphan*/  tps65910_rtc_ops ; 

__attribute__((used)) static int tps65910_rtc_probe(struct platform_device *pdev)
{
	struct tps65910 *tps65910 = NULL;
	struct tps65910_rtc *tps_rtc = NULL;
	int ret;
	int irq;
	u32 rtc_reg;

	tps65910 = dev_get_drvdata(pdev->dev.parent);

	tps_rtc = devm_kzalloc(&pdev->dev, sizeof(struct tps65910_rtc),
			GFP_KERNEL);
	if (!tps_rtc)
		return -ENOMEM;

	tps_rtc->rtc = devm_rtc_allocate_device(&pdev->dev);
	if (IS_ERR(tps_rtc->rtc))
		return PTR_ERR(tps_rtc->rtc);

	/* Clear pending interrupts */
	ret = regmap_read(tps65910->regmap, TPS65910_RTC_STATUS, &rtc_reg);
	if (ret < 0)
		return ret;

	ret = regmap_write(tps65910->regmap, TPS65910_RTC_STATUS, rtc_reg);
	if (ret < 0)
		return ret;

	dev_dbg(&pdev->dev, "Enabling rtc-tps65910.\n");

	/* Enable RTC digital power domain */
	ret = regmap_update_bits(tps65910->regmap, TPS65910_DEVCTRL,
		DEVCTRL_RTC_PWDN_MASK, 0 << DEVCTRL_RTC_PWDN_SHIFT);
	if (ret < 0)
		return ret;

	rtc_reg = TPS65910_RTC_CTRL_STOP_RTC;
	ret = regmap_write(tps65910->regmap, TPS65910_RTC_CTRL, rtc_reg);
	if (ret < 0)
		return ret;

	platform_set_drvdata(pdev, tps_rtc);

	irq  = platform_get_irq(pdev, 0);
	if (irq <= 0) {
		dev_warn(&pdev->dev, "Wake up is not possible as irq = %d\n",
			irq);
		return -ENXIO;
	}

	ret = devm_request_threaded_irq(&pdev->dev, irq, NULL,
		tps65910_rtc_interrupt, IRQF_TRIGGER_LOW,
		dev_name(&pdev->dev), &pdev->dev);
	if (ret < 0) {
		dev_err(&pdev->dev, "IRQ is not free.\n");
		return ret;
	}
	tps_rtc->irq = irq;
	device_set_wakeup_capable(&pdev->dev, 1);

	tps_rtc->rtc->ops = &tps65910_rtc_ops;
	tps_rtc->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	tps_rtc->rtc->range_max = RTC_TIMESTAMP_END_2099;

	return rtc_register_device(tps_rtc->rtc);
}