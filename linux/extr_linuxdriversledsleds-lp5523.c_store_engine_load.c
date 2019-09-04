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
struct lp55xx_chip {int engine_idx; int /*<<< orphan*/  lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct lp55xx_led* i2c_get_clientdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lp5523_load_engine_and_select_page (struct lp55xx_chip*) ; 
 int lp5523_update_program_memory (struct lp55xx_chip*,char const*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t store_engine_load(struct device *dev,
			     struct device_attribute *attr,
			     const char *buf, size_t len, int nr)
{
	struct lp55xx_led *led = i2c_get_clientdata(to_i2c_client(dev));
	struct lp55xx_chip *chip = led->chip;
	int ret;

	mutex_lock(&chip->lock);

	chip->engine_idx = nr;
	lp5523_load_engine_and_select_page(chip);
	ret = lp5523_update_program_memory(chip, buf, len);

	mutex_unlock(&chip->lock);

	return ret;
}