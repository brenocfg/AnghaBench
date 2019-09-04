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
struct lp55xx_chip {int engine_idx; int /*<<< orphan*/  lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
typedef  enum lp55xx_engine_index { ____Placeholder_lp55xx_engine_index } lp55xx_engine_index ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  LP5562_ENG1_FOR_W ; 
 int /*<<< orphan*/  LP5562_ENG2_FOR_W ; 
 int /*<<< orphan*/  LP5562_ENG3_FOR_W ; 
 int /*<<< orphan*/  LP5562_ENG_FOR_RGB_M ; 
 int /*<<< orphan*/  LP5562_ENG_FOR_W_M ; 
 int /*<<< orphan*/  LP5562_ENG_SEL_RGB ; 
 int /*<<< orphan*/  LP5562_REG_ENG_SEL ; 
#define  LP55XX_ENGINE_1 130 
#define  LP55XX_ENGINE_2 129 
#define  LP55XX_ENGINE_3 128 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct lp55xx_led* i2c_get_clientdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lp55xx_update_bits (struct lp55xx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sysfs_streq (char const*,char*) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t lp5562_store_engine_mux(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t len)
{
	struct lp55xx_led *led = i2c_get_clientdata(to_i2c_client(dev));
	struct lp55xx_chip *chip = led->chip;
	u8 mask;
	u8 val;

	/* LED map
	 * R ... Engine 1 (fixed)
	 * G ... Engine 2 (fixed)
	 * B ... Engine 3 (fixed)
	 * W ... Engine 1 or 2 or 3
	 */

	if (sysfs_streq(buf, "RGB")) {
		mask = LP5562_ENG_FOR_RGB_M;
		val = LP5562_ENG_SEL_RGB;
	} else if (sysfs_streq(buf, "W")) {
		enum lp55xx_engine_index idx = chip->engine_idx;

		mask = LP5562_ENG_FOR_W_M;
		switch (idx) {
		case LP55XX_ENGINE_1:
			val = LP5562_ENG1_FOR_W;
			break;
		case LP55XX_ENGINE_2:
			val = LP5562_ENG2_FOR_W;
			break;
		case LP55XX_ENGINE_3:
			val = LP5562_ENG3_FOR_W;
			break;
		default:
			return -EINVAL;
		}

	} else {
		dev_err(dev, "choose RGB or W\n");
		return -EINVAL;
	}

	mutex_lock(&chip->lock);
	lp55xx_update_bits(chip, LP5562_REG_ENG_SEL, mask, val);
	mutex_unlock(&chip->lock);

	return len;
}