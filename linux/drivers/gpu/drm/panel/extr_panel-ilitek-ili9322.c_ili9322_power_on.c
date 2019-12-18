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
struct ili9322 {int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  dev; int /*<<< orphan*/  supplies; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ili9322_power_on(struct ili9322 *ili)
{
	int ret;

	/* Assert RESET */
	gpiod_set_value(ili->reset_gpio, 1);

	ret = regulator_bulk_enable(ARRAY_SIZE(ili->supplies), ili->supplies);
	if (ret < 0) {
		dev_err(ili->dev, "unable to enable regulators\n");
		return ret;
	}
	msleep(20);

	/* De-assert RESET */
	gpiod_set_value(ili->reset_gpio, 0);

	msleep(10);

	return 0;
}