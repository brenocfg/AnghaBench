#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ds2404_platform_data {int dummy; } ;
struct ds2404 {TYPE_2__* rtc; TYPE_1__* gpio; } ;
struct TYPE_7__ {int /*<<< orphan*/  range_max; int /*<<< orphan*/ * ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 size_t DS2404_CLK ; 
 size_t DS2404_DQ ; 
 size_t DS2404_RST ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int PTR_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  U32_MAX ; 
 struct ds2404_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_add_action_or_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ds2404*) ; 
 struct ds2404* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* devm_rtc_allocate_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ds2404_enable_osc (int /*<<< orphan*/ *) ; 
 int ds2404_gpio_map (struct ds2404*,struct platform_device*,struct ds2404_platform_data*) ; 
 int /*<<< orphan*/  ds2404_gpio_unmap ; 
 int /*<<< orphan*/  ds2404_rtc_ops ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ds2404*) ; 
 int rtc_register_device (TYPE_2__*) ; 

__attribute__((used)) static int rtc_probe(struct platform_device *pdev)
{
	struct ds2404_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct ds2404 *chip;
	int retval = -EBUSY;

	chip = devm_kzalloc(&pdev->dev, sizeof(struct ds2404), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	chip->rtc = devm_rtc_allocate_device(&pdev->dev);
	if (IS_ERR(chip->rtc))
		return PTR_ERR(chip->rtc);

	retval = ds2404_gpio_map(chip, pdev, pdata);
	if (retval)
		return retval;

	retval = devm_add_action_or_reset(&pdev->dev, ds2404_gpio_unmap, chip);
	if (retval)
		return retval;

	dev_info(&pdev->dev, "using GPIOs RST:%d, CLK:%d, DQ:%d\n",
		 chip->gpio[DS2404_RST].gpio, chip->gpio[DS2404_CLK].gpio,
		 chip->gpio[DS2404_DQ].gpio);

	platform_set_drvdata(pdev, chip);

	chip->rtc->ops = &ds2404_rtc_ops;
	chip->rtc->range_max = U32_MAX;

	retval = rtc_register_device(chip->rtc);
	if (retval)
		return retval;

	ds2404_enable_osc(&pdev->dev);
	return 0;
}