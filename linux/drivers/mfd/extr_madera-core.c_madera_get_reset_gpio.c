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
struct TYPE_2__ {struct gpio_desc* reset; } ;
struct madera {TYPE_1__ pdata; int /*<<< orphan*/  dev; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct gpio_desc* devm_gpiod_get_optional (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int madera_get_reset_gpio(struct madera *madera)
{
	struct gpio_desc *reset;
	int ret;

	if (madera->pdata.reset)
		return 0;

	reset = devm_gpiod_get_optional(madera->dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(reset)) {
		ret = PTR_ERR(reset);
		if (ret != -EPROBE_DEFER)
			dev_err(madera->dev, "Failed to request /RESET: %d\n",
				ret);
		return ret;
	}

	/*
	 * A hard reset is needed for full reset of the chip. We allow running
	 * without hard reset only because it can be useful for early
	 * prototyping and some debugging, but we need to warn it's not ideal.
	 */
	if (!reset)
		dev_warn(madera->dev,
			 "Running without reset GPIO is not recommended\n");

	madera->pdata.reset = reset;

	return 0;
}