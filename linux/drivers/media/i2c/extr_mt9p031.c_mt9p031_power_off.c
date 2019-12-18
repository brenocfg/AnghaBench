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
struct mt9p031 {scalar_t__ clk; int /*<<< orphan*/  regulators; scalar_t__ reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void mt9p031_power_off(struct mt9p031 *mt9p031)
{
	if (mt9p031->reset) {
		gpiod_set_value(mt9p031->reset, 1);
		usleep_range(1000, 2000);
	}

	regulator_bulk_disable(ARRAY_SIZE(mt9p031->regulators),
			       mt9p031->regulators);

	if (mt9p031->clk)
		clk_disable_unprepare(mt9p031->clk);
}