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
struct rc5t583_rtc {int /*<<< orphan*/  rtc; } ;
struct rc5t583_platform_data {int irq_base; } ;
struct rc5t583 {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_TRIGGER_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ RC5T583_IRQ_YALE ; 
 int /*<<< orphan*/  RC5T583_RTC_ADJ ; 
 int /*<<< orphan*/  RC5T583_RTC_CTL2 ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct rc5t583* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct rc5t583_platform_data* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_1__*,int) ; 
 struct rc5t583_rtc* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  devm_rtc_device_register (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rc5t583_rtc*) ; 
 int /*<<< orphan*/  rc5t583_rtc_interrupt ; 
 int /*<<< orphan*/  rc5t583_rtc_ops ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rc5t583_rtc_probe(struct platform_device *pdev)
{
	struct rc5t583 *rc5t583 = dev_get_drvdata(pdev->dev.parent);
	struct rc5t583_rtc *ricoh_rtc;
	struct rc5t583_platform_data *pmic_plat_data;
	int ret;
	int irq;

	ricoh_rtc = devm_kzalloc(&pdev->dev, sizeof(struct rc5t583_rtc),
			GFP_KERNEL);
	if (!ricoh_rtc)
		return -ENOMEM;

	platform_set_drvdata(pdev, ricoh_rtc);

	/* Clear pending interrupts */
	ret = regmap_write(rc5t583->regmap, RC5T583_RTC_CTL2, 0);
	if (ret < 0)
		return ret;

	/* clear RTC Adjust register */
	ret = regmap_write(rc5t583->regmap, RC5T583_RTC_ADJ, 0);
	if (ret < 0) {
		dev_err(&pdev->dev, "unable to program rtc_adjust reg\n");
		return -EBUSY;
	}

	pmic_plat_data = dev_get_platdata(rc5t583->dev);
	irq = pmic_plat_data->irq_base;
	if (irq <= 0) {
		dev_warn(&pdev->dev, "Wake up is not possible as irq = %d\n",
			irq);
		return ret;
	}

	irq += RC5T583_IRQ_YALE;
	ret = devm_request_threaded_irq(&pdev->dev, irq, NULL,
		rc5t583_rtc_interrupt, IRQF_TRIGGER_LOW,
		"rtc-rc5t583", &pdev->dev);
	if (ret < 0) {
		dev_err(&pdev->dev, "IRQ is not free.\n");
		return ret;
	}
	device_init_wakeup(&pdev->dev, 1);

	ricoh_rtc->rtc = devm_rtc_device_register(&pdev->dev, pdev->name,
		&rc5t583_rtc_ops, THIS_MODULE);
	if (IS_ERR(ricoh_rtc->rtc)) {
		ret = PTR_ERR(ricoh_rtc->rtc);
		dev_err(&pdev->dev, "RTC device register: err %d\n", ret);
		return ret;
	}

	return 0;
}