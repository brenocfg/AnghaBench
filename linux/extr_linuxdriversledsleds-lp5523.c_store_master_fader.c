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
typedef  int /*<<< orphan*/  u8 ;
struct lp55xx_led {struct lp55xx_chip* chip; } ;
struct lp55xx_chip {int /*<<< orphan*/  lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ LP5523_REG_MASTER_FADER_BASE ; 
 struct lp55xx_led* i2c_get_clientdata (int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int lp55xx_write (struct lp55xx_chip*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t store_master_fader(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t len, int nr)
{
	struct lp55xx_led *led = i2c_get_clientdata(to_i2c_client(dev));
	struct lp55xx_chip *chip = led->chip;
	int ret;
	unsigned long val;

	if (kstrtoul(buf, 0, &val))
		return -EINVAL;

	if (val > 0xff)
		return -EINVAL;

	mutex_lock(&chip->lock);
	ret = lp55xx_write(chip, LP5523_REG_MASTER_FADER_BASE + nr - 1,
			   (u8)val);
	mutex_unlock(&chip->lock);

	if (ret == 0)
		ret = len;

	return ret;
}