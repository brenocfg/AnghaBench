#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct max77686_rtc_info {int rtc_irq; TYPE_2__* dev; int /*<<< orphan*/  rtc_irq_data; TYPE_1__* drv_data; scalar_t__ rtc_regmap; scalar_t__ rtc; scalar_t__ regmap; } ;
struct i2c_client {int irq; int /*<<< orphan*/  adapter; } ;
struct device {int dummy; } ;
struct TYPE_6__ {struct device* parent; } ;
struct TYPE_5__ {int /*<<< orphan*/  rtc_irq_chip; int /*<<< orphan*/  rtc_i2c_addr; scalar_t__ rtc_irq_from_platform; } ;

/* Variables and functions */
 int ENODEV ; 
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 int IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  MAX77686_INVALID_I2C_ADDR ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 scalar_t__ dev_get_regmap (struct device*,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_i2c_new_dummy_device (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_regmap_init_i2c (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max77686_rtc_regmap_config ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int regmap_add_irq_chip (scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct platform_device* to_platform_device (TYPE_2__*) ; 

__attribute__((used)) static int max77686_init_rtc_regmap(struct max77686_rtc_info *info)
{
	struct device *parent = info->dev->parent;
	struct i2c_client *parent_i2c = to_i2c_client(parent);
	int ret;

	if (info->drv_data->rtc_irq_from_platform) {
		struct platform_device *pdev = to_platform_device(info->dev);

		info->rtc_irq = platform_get_irq(pdev, 0);
		if (info->rtc_irq < 0)
			return info->rtc_irq;
	} else {
		info->rtc_irq =  parent_i2c->irq;
	}

	info->regmap = dev_get_regmap(parent, NULL);
	if (!info->regmap) {
		dev_err(info->dev, "Failed to get rtc regmap\n");
		return -ENODEV;
	}

	if (info->drv_data->rtc_i2c_addr == MAX77686_INVALID_I2C_ADDR) {
		info->rtc_regmap = info->regmap;
		goto add_rtc_irq;
	}

	info->rtc = devm_i2c_new_dummy_device(info->dev, parent_i2c->adapter,
					      info->drv_data->rtc_i2c_addr);
	if (IS_ERR(info->rtc)) {
		dev_err(info->dev, "Failed to allocate I2C device for RTC\n");
		return PTR_ERR(info->rtc);
	}

	info->rtc_regmap = devm_regmap_init_i2c(info->rtc,
						&max77686_rtc_regmap_config);
	if (IS_ERR(info->rtc_regmap)) {
		ret = PTR_ERR(info->rtc_regmap);
		dev_err(info->dev, "Failed to allocate RTC regmap: %d\n", ret);
		return ret;
	}

add_rtc_irq:
	ret = regmap_add_irq_chip(info->rtc_regmap, info->rtc_irq,
				  IRQF_TRIGGER_FALLING | IRQF_ONESHOT |
				  IRQF_SHARED, 0, info->drv_data->rtc_irq_chip,
				  &info->rtc_irq_data);
	if (ret < 0) {
		dev_err(info->dev, "Failed to add RTC irq chip: %d\n", ret);
		return ret;
	}

	return 0;
}