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
struct device {int dummy; } ;
struct ad7780_state {void* filter_gpio; void* gain_gpio; TYPE_1__* chip_info; void* powerdown_gpio; } ;
struct TYPE_2__ {int /*<<< orphan*/  is_ad778x; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad7780_init_gpios(struct device *dev, struct ad7780_state *st)
{
	int ret;

	st->powerdown_gpio = devm_gpiod_get_optional(dev,
						     "powerdown",
						     GPIOD_OUT_LOW);
	if (IS_ERR(st->powerdown_gpio)) {
		ret = PTR_ERR(st->powerdown_gpio);
		dev_err(dev, "Failed to request powerdown GPIO: %d\n", ret);
		return ret;
	}

	if (!st->chip_info->is_ad778x)
		return 0;


	st->gain_gpio = devm_gpiod_get_optional(dev,
						"adi,gain",
						GPIOD_OUT_HIGH);
	if (IS_ERR(st->gain_gpio)) {
		ret = PTR_ERR(st->gain_gpio);
		dev_err(dev, "Failed to request gain GPIO: %d\n", ret);
		return ret;
	}

	st->filter_gpio = devm_gpiod_get_optional(dev,
						  "adi,filter",
						  GPIOD_OUT_HIGH);
	if (IS_ERR(st->filter_gpio)) {
		ret = PTR_ERR(st->filter_gpio);
		dev_err(dev, "Failed to request filter GPIO: %d\n", ret);
		return ret;
	}

	return 0;
}