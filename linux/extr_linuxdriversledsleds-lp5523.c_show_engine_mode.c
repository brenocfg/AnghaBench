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
struct lp55xx_led {struct lp55xx_chip* chip; } ;
struct lp55xx_chip {TYPE_1__* engines; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  enum lp55xx_engine_mode { ____Placeholder_lp55xx_engine_mode } lp55xx_engine_mode ;
struct TYPE_2__ {int mode; } ;

/* Variables and functions */
#define  LP55XX_ENGINE_DISABLED 130 
#define  LP55XX_ENGINE_LOAD 129 
#define  LP55XX_ENGINE_RUN 128 
 struct lp55xx_led* i2c_get_clientdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t show_engine_mode(struct device *dev,
				struct device_attribute *attr,
				char *buf, int nr)
{
	struct lp55xx_led *led = i2c_get_clientdata(to_i2c_client(dev));
	struct lp55xx_chip *chip = led->chip;
	enum lp55xx_engine_mode mode = chip->engines[nr - 1].mode;

	switch (mode) {
	case LP55XX_ENGINE_RUN:
		return sprintf(buf, "run\n");
	case LP55XX_ENGINE_LOAD:
		return sprintf(buf, "load\n");
	case LP55XX_ENGINE_DISABLED:
	default:
		return sprintf(buf, "disabled\n");
	}
}