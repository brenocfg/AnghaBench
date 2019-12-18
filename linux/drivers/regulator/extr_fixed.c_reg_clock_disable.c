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
struct regulator_dev {int dummy; } ;
struct fixed_voltage_data {int /*<<< orphan*/  clk_enable_counter; int /*<<< orphan*/  enable_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct fixed_voltage_data* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int reg_clock_disable(struct regulator_dev *rdev)
{
	struct fixed_voltage_data *priv = rdev_get_drvdata(rdev);

	clk_disable_unprepare(priv->enable_clock);
	priv->clk_enable_counter--;

	return 0;
}