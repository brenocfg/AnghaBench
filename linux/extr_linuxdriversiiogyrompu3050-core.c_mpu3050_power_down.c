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
struct mpu3050 {int /*<<< orphan*/  dev; int /*<<< orphan*/  regs; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPU3050_PWR_MGM ; 
 int /*<<< orphan*/  MPU3050_PWR_MGM_SLEEP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpu3050_power_down(struct mpu3050 *mpu3050)
{
	int ret;

	/*
	 * Put MPU-3050 into sleep mode before cutting regulators.
	 * This is important, because we may not be the sole user
	 * of the regulator so the power may stay on after this, and
	 * then we would be wasting power unless we go to sleep mode
	 * first.
	 */
	ret = regmap_update_bits(mpu3050->map, MPU3050_PWR_MGM,
				 MPU3050_PWR_MGM_SLEEP, MPU3050_PWR_MGM_SLEEP);
	if (ret)
		dev_err(mpu3050->dev, "error putting to sleep\n");

	ret = regulator_bulk_disable(ARRAY_SIZE(mpu3050->regs), mpu3050->regs);
	if (ret)
		dev_err(mpu3050->dev, "error disabling regulators\n");

	return 0;
}