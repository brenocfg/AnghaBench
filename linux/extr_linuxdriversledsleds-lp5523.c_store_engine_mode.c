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
struct lp55xx_engine {int /*<<< orphan*/  mode; } ;
struct lp55xx_chip {int engine_idx; int /*<<< orphan*/  lock; struct lp55xx_engine* engines; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  LP55XX_ENGINE_DISABLED ; 
 int /*<<< orphan*/  LP55XX_ENGINE_LOAD ; 
 int /*<<< orphan*/  LP55XX_ENGINE_RUN ; 
 struct lp55xx_led* i2c_get_clientdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lp5523_load_engine (struct lp55xx_chip*) ; 
 int /*<<< orphan*/  lp5523_run_engine (struct lp55xx_chip*,int) ; 
 int /*<<< orphan*/  lp5523_stop_engine (struct lp55xx_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t store_engine_mode(struct device *dev,
				 struct device_attribute *attr,
				 const char *buf, size_t len, int nr)
{
	struct lp55xx_led *led = i2c_get_clientdata(to_i2c_client(dev));
	struct lp55xx_chip *chip = led->chip;
	struct lp55xx_engine *engine = &chip->engines[nr - 1];

	mutex_lock(&chip->lock);

	chip->engine_idx = nr;

	if (!strncmp(buf, "run", 3)) {
		lp5523_run_engine(chip, true);
		engine->mode = LP55XX_ENGINE_RUN;
	} else if (!strncmp(buf, "load", 4)) {
		lp5523_stop_engine(chip);
		lp5523_load_engine(chip);
		engine->mode = LP55XX_ENGINE_LOAD;
	} else if (!strncmp(buf, "disabled", 8)) {
		lp5523_stop_engine(chip);
		engine->mode = LP55XX_ENGINE_DISABLED;
	}

	mutex_unlock(&chip->lock);

	return len;
}