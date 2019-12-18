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
struct et8ek8_sensor {int /*<<< orphan*/  vana; int /*<<< orphan*/  ext_clk; int /*<<< orphan*/  reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int et8ek8_power_off(struct et8ek8_sensor *sensor)
{
	gpiod_set_value(sensor->reset, 0);
	udelay(1);

	clk_disable_unprepare(sensor->ext_clk);

	return regulator_disable(sensor->vana);
}