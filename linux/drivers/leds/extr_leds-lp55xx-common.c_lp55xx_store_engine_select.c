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
struct lp55xx_led {struct lp55xx_chip* chip; } ;
struct lp55xx_chip {unsigned long engine_idx; int /*<<< orphan*/  lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
#define  LP55XX_ENGINE_1 130 
#define  LP55XX_ENGINE_2 129 
#define  LP55XX_ENGINE_3 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct lp55xx_led* i2c_get_clientdata (int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int lp55xx_request_firmware (struct lp55xx_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t lp55xx_store_engine_select(struct device *dev,
			     struct device_attribute *attr,
			     const char *buf, size_t len)
{
	struct lp55xx_led *led = i2c_get_clientdata(to_i2c_client(dev));
	struct lp55xx_chip *chip = led->chip;
	unsigned long val;
	int ret;

	if (kstrtoul(buf, 0, &val))
		return -EINVAL;

	/* select the engine to be run */

	switch (val) {
	case LP55XX_ENGINE_1:
	case LP55XX_ENGINE_2:
	case LP55XX_ENGINE_3:
		mutex_lock(&chip->lock);
		chip->engine_idx = val;
		ret = lp55xx_request_firmware(chip);
		mutex_unlock(&chip->lock);
		break;
	default:
		dev_err(dev, "%lu: invalid engine index. (1, 2, 3)\n", val);
		return -EINVAL;
	}

	if (ret) {
		dev_err(dev, "request firmware err: %d\n", ret);
		return ret;
	}

	return len;
}