#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_3__ dev; } ;
struct ac100_rtc_dev {scalar_t__ irq; TYPE_1__* rtc; int /*<<< orphan*/  regmap; TYPE_3__* dev; } ;
struct ac100_dev {int /*<<< orphan*/  regmap; } ;
struct TYPE_10__ {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC100_ALM_INT_ENA ; 
 int /*<<< orphan*/  AC100_ALM_INT_ENABLE ; 
 int /*<<< orphan*/  AC100_ALM_INT_STA ; 
 int /*<<< orphan*/  AC100_RTC_CTRL ; 
 int /*<<< orphan*/  AC100_RTC_CTRL_24HOUR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  ac100_rtc_irq ; 
 int /*<<< orphan*/  ac100_rtc_ops ; 
 int ac100_rtc_register_clks (struct ac100_rtc_dev*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 struct ac100_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 struct ac100_rtc_dev* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct ac100_rtc_dev*) ; 
 TYPE_1__* devm_rtc_allocate_device (TYPE_3__*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ac100_rtc_dev*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtc_register_device (TYPE_1__*) ; 

__attribute__((used)) static int ac100_rtc_probe(struct platform_device *pdev)
{
	struct ac100_dev *ac100 = dev_get_drvdata(pdev->dev.parent);
	struct ac100_rtc_dev *chip;
	int ret;

	chip = devm_kzalloc(&pdev->dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	platform_set_drvdata(pdev, chip);
	chip->dev = &pdev->dev;
	chip->regmap = ac100->regmap;

	chip->irq = platform_get_irq(pdev, 0);
	if (chip->irq < 0)
		return chip->irq;

	chip->rtc = devm_rtc_allocate_device(&pdev->dev);
	if (IS_ERR(chip->rtc))
		return PTR_ERR(chip->rtc);

	chip->rtc->ops = &ac100_rtc_ops;

	ret = devm_request_threaded_irq(&pdev->dev, chip->irq, NULL,
					ac100_rtc_irq,
					IRQF_SHARED | IRQF_ONESHOT,
					dev_name(&pdev->dev), chip);
	if (ret) {
		dev_err(&pdev->dev, "Could not request IRQ\n");
		return ret;
	}

	/* always use 24 hour mode */
	regmap_write_bits(chip->regmap, AC100_RTC_CTRL, AC100_RTC_CTRL_24HOUR,
			  AC100_RTC_CTRL_24HOUR);

	/* disable counter alarm interrupt */
	regmap_write(chip->regmap, AC100_ALM_INT_ENA, 0);

	/* clear counter alarm pending interrupts */
	regmap_write(chip->regmap, AC100_ALM_INT_STA, AC100_ALM_INT_ENABLE);

	ret = ac100_rtc_register_clks(chip);
	if (ret)
		return ret;

	return rtc_register_device(chip->rtc);
}