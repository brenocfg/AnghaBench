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
struct s5k6a3 {int /*<<< orphan*/  dev; int /*<<< orphan*/  clock; TYPE_1__* supplies; int /*<<< orphan*/  gpio_reset; } ;
struct TYPE_2__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int S5K6A3_NUM_SUPPLIES ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __s5k6a3_power_off(struct s5k6a3 *sensor)
{
	int i;

	gpio_set_value(sensor->gpio_reset, 0);

	for (i = S5K6A3_NUM_SUPPLIES - 1; i >= 0; i--)
		regulator_disable(sensor->supplies[i].consumer);

	clk_disable_unprepare(sensor->clock);
	pm_runtime_put(sensor->dev);
	return 0;
}