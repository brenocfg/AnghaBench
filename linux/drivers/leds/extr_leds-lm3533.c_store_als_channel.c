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
typedef  unsigned int u8 ;
struct lm3533_led {int /*<<< orphan*/  lm3533; } ;
struct led_classdev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int LM3533_ALS_CHANNEL_LV_MAX ; 
 unsigned int LM3533_ALS_CHANNEL_LV_MIN ; 
 unsigned int LM3533_REG_CTRLBANK_BCONF_ALS_CHANNEL_MASK ; 
 int /*<<< orphan*/  LM3533_REG_CTRLBANK_BCONF_BASE ; 
 struct led_classdev* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 
 unsigned int lm3533_led_get_lv_reg (struct lm3533_led*,int /*<<< orphan*/ ) ; 
 int lm3533_update (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 struct lm3533_led* to_lm3533_led (struct led_classdev*) ; 

__attribute__((used)) static ssize_t store_als_channel(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t len)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct lm3533_led *led = to_lm3533_led(led_cdev);
	unsigned channel;
	u8 reg;
	u8 val;
	u8 mask;
	int ret;

	if (kstrtouint(buf, 0, &channel))
		return -EINVAL;

	if (channel < LM3533_ALS_CHANNEL_LV_MIN ||
					channel > LM3533_ALS_CHANNEL_LV_MAX)
		return -EINVAL;

	reg = lm3533_led_get_lv_reg(led, LM3533_REG_CTRLBANK_BCONF_BASE);
	mask = LM3533_REG_CTRLBANK_BCONF_ALS_CHANNEL_MASK;
	val = channel - 1;

	ret = lm3533_update(led->lm3533, reg, val, mask);
	if (ret)
		return ret;

	return len;
}