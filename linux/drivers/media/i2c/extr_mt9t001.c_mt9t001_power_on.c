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
struct mt9t001 {int /*<<< orphan*/  regulators; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt9t001_power_on(struct mt9t001 *mt9t001)
{
	int ret;

	/* Bring up the supplies */
	ret = regulator_bulk_enable(ARRAY_SIZE(mt9t001->regulators),
				   mt9t001->regulators);
	if (ret < 0)
		return ret;

	/* Enable clock */
	ret = clk_prepare_enable(mt9t001->clk);
	if (ret < 0)
		regulator_bulk_disable(ARRAY_SIZE(mt9t001->regulators),
				       mt9t001->regulators);

	return ret;
}