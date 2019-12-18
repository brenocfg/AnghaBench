#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct palmas_rtc {int /*<<< orphan*/  irq; int /*<<< orphan*/  rtc; TYPE_1__* dev; } ;
struct palmas {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PALMAS_BACKUP_BATTERY_CTRL ; 
 unsigned int PALMAS_BACKUP_BATTERY_CTRL_BBS_BBC_LOW_ICHRG ; 
 unsigned int PALMAS_BACKUP_BATTERY_CTRL_BB_CHG_EN ; 
 int /*<<< orphan*/  PALMAS_PMU_CONTROL_BASE ; 
 int /*<<< orphan*/  PALMAS_RTC_BASE ; 
 int /*<<< orphan*/  PALMAS_RTC_CTRL_REG ; 
 unsigned int PALMAS_RTC_CTRL_REG_STOP_RTC ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 struct palmas* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_1__*,int) ; 
 struct palmas_rtc* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct palmas_rtc*) ; 
 int /*<<< orphan*/  devm_rtc_device_register (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int of_property_read_bool (scalar_t__,char*) ; 
 int palmas_clear_interrupts (TYPE_1__*) ; 
 int /*<<< orphan*/  palmas_rtc_interrupt ; 
 int /*<<< orphan*/  palmas_rtc_ops ; 
 int palmas_update_bits (struct palmas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct palmas_rtc*) ; 

__attribute__((used)) static int palmas_rtc_probe(struct platform_device *pdev)
{
	struct palmas *palmas = dev_get_drvdata(pdev->dev.parent);
	struct palmas_rtc *palmas_rtc = NULL;
	int ret;
	bool enable_bb_charging = false;
	bool high_bb_charging = false;

	if (pdev->dev.of_node) {
		enable_bb_charging = of_property_read_bool(pdev->dev.of_node,
					"ti,backup-battery-chargeable");
		high_bb_charging = of_property_read_bool(pdev->dev.of_node,
					"ti,backup-battery-charge-high-current");
	}

	palmas_rtc = devm_kzalloc(&pdev->dev, sizeof(struct palmas_rtc),
			GFP_KERNEL);
	if (!palmas_rtc)
		return -ENOMEM;

	/* Clear pending interrupts */
	ret = palmas_clear_interrupts(&pdev->dev);
	if (ret < 0) {
		dev_err(&pdev->dev, "clear RTC int failed, err = %d\n", ret);
		return ret;
	}

	palmas_rtc->dev = &pdev->dev;
	platform_set_drvdata(pdev, palmas_rtc);

	if (enable_bb_charging) {
		unsigned reg = PALMAS_BACKUP_BATTERY_CTRL_BBS_BBC_LOW_ICHRG;

		if (high_bb_charging)
			reg = 0;

		ret = palmas_update_bits(palmas, PALMAS_PMU_CONTROL_BASE,
			PALMAS_BACKUP_BATTERY_CTRL,
			PALMAS_BACKUP_BATTERY_CTRL_BBS_BBC_LOW_ICHRG, reg);
		if (ret < 0) {
			dev_err(&pdev->dev,
				"BACKUP_BATTERY_CTRL update failed, %d\n", ret);
			return ret;
		}

		ret = palmas_update_bits(palmas, PALMAS_PMU_CONTROL_BASE,
			PALMAS_BACKUP_BATTERY_CTRL,
			PALMAS_BACKUP_BATTERY_CTRL_BB_CHG_EN,
			PALMAS_BACKUP_BATTERY_CTRL_BB_CHG_EN);
		if (ret < 0) {
			dev_err(&pdev->dev,
				"BACKUP_BATTERY_CTRL update failed, %d\n", ret);
			return ret;
		}
	}

	/* Start RTC */
	ret = palmas_update_bits(palmas, PALMAS_RTC_BASE, PALMAS_RTC_CTRL_REG,
			PALMAS_RTC_CTRL_REG_STOP_RTC,
			PALMAS_RTC_CTRL_REG_STOP_RTC);
	if (ret < 0) {
		dev_err(&pdev->dev, "RTC_CTRL write failed, err = %d\n", ret);
		return ret;
	}

	palmas_rtc->irq = platform_get_irq(pdev, 0);

	device_init_wakeup(&pdev->dev, 1);
	palmas_rtc->rtc = devm_rtc_device_register(&pdev->dev, pdev->name,
				&palmas_rtc_ops, THIS_MODULE);
	if (IS_ERR(palmas_rtc->rtc)) {
		ret = PTR_ERR(palmas_rtc->rtc);
		dev_err(&pdev->dev, "RTC register failed, err = %d\n", ret);
		return ret;
	}

	ret = devm_request_threaded_irq(&pdev->dev, palmas_rtc->irq, NULL,
			palmas_rtc_interrupt,
			IRQF_TRIGGER_LOW | IRQF_ONESHOT,
			dev_name(&pdev->dev), palmas_rtc);
	if (ret < 0) {
		dev_err(&pdev->dev, "IRQ request failed, err = %d\n", ret);
		return ret;
	}

	return 0;
}