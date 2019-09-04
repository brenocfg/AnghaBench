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
struct ov965x {scalar_t__ streaming; int /*<<< orphan*/  clk; int /*<<< orphan*/ * gpios; } ;

/* Variables and functions */
 size_t GPIO_PWDN ; 
 size_t GPIO_RST ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int __ov965x_set_power(struct ov965x *ov965x, int on)
{
	if (on) {
		int ret = clk_prepare_enable(ov965x->clk);

		if (ret)
			return ret;

		gpiod_set_value_cansleep(ov965x->gpios[GPIO_PWDN], 0);
		gpiod_set_value_cansleep(ov965x->gpios[GPIO_RST], 0);
		msleep(25);
	} else {
		gpiod_set_value_cansleep(ov965x->gpios[GPIO_RST], 1);
		gpiod_set_value_cansleep(ov965x->gpios[GPIO_PWDN], 1);

		clk_disable_unprepare(ov965x->clk);
	}

	ov965x->streaming = 0;

	return 0;
}