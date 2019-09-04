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
struct mt9p031 {scalar_t__ reset; int /*<<< orphan*/  regulators; scalar_t__ clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int mt9p031_power_on(struct mt9p031 *mt9p031)
{
	int ret;

	/* Ensure RESET_BAR is active */
	if (mt9p031->reset) {
		gpiod_set_value(mt9p031->reset, 1);
		usleep_range(1000, 2000);
	}

	/* Bring up the supplies */
	ret = regulator_bulk_enable(ARRAY_SIZE(mt9p031->regulators),
				   mt9p031->regulators);
	if (ret < 0)
		return ret;

	/* Enable clock */
	if (mt9p031->clk) {
		ret = clk_prepare_enable(mt9p031->clk);
		if (ret) {
			regulator_bulk_disable(ARRAY_SIZE(mt9p031->regulators),
					       mt9p031->regulators);
			return ret;
		}
	}

	/* Now RESET_BAR must be high */
	if (mt9p031->reset) {
		gpiod_set_value(mt9p031->reset, 0);
		usleep_range(1000, 2000);
	}

	return 0;
}