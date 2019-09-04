#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lp55xx_platform_data {int /*<<< orphan*/  enable_gpio; } ;
struct lp55xx_device_config {int dummy; } ;
struct lp55xx_chip {struct lp55xx_device_config* cfg; struct lp55xx_platform_data* pdata; TYPE_1__* cl; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIOF_DIR_OUT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int devm_gpio_request_one (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lp55xx_deinit_device (struct lp55xx_chip*) ; 
 int lp55xx_detect_device (struct lp55xx_chip*) ; 
 int lp55xx_post_init_device (struct lp55xx_chip*) ; 
 int /*<<< orphan*/  lp55xx_reset_device (struct lp55xx_chip*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int lp55xx_init_device(struct lp55xx_chip *chip)
{
	struct lp55xx_platform_data *pdata;
	struct lp55xx_device_config *cfg;
	struct device *dev = &chip->cl->dev;
	int ret = 0;

	WARN_ON(!chip);

	pdata = chip->pdata;
	cfg = chip->cfg;

	if (!pdata || !cfg)
		return -EINVAL;

	if (gpio_is_valid(pdata->enable_gpio)) {
		ret = devm_gpio_request_one(dev, pdata->enable_gpio,
					    GPIOF_DIR_OUT, "lp5523_enable");
		if (ret < 0) {
			dev_err(dev, "could not acquire enable gpio (err=%d)\n",
				ret);
			goto err;
		}

		gpio_set_value(pdata->enable_gpio, 0);
		usleep_range(1000, 2000); /* Keep enable down at least 1ms */
		gpio_set_value(pdata->enable_gpio, 1);
		usleep_range(1000, 2000); /* 500us abs min. */
	}

	lp55xx_reset_device(chip);

	/*
	 * Exact value is not available. 10 - 20ms
	 * appears to be enough for reset.
	 */
	usleep_range(10000, 20000);

	ret = lp55xx_detect_device(chip);
	if (ret) {
		dev_err(dev, "device detection err: %d\n", ret);
		goto err;
	}

	/* chip specific initialization */
	ret = lp55xx_post_init_device(chip);
	if (ret) {
		dev_err(dev, "post init device err: %d\n", ret);
		goto err_post_init;
	}

	return 0;

err_post_init:
	lp55xx_deinit_device(chip);
err:
	return ret;
}