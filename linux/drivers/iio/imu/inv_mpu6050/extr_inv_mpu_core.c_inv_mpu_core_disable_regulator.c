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
struct inv_mpu6050_state {int /*<<< orphan*/  map; int /*<<< orphan*/  vddio_supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  regmap_get_device (int /*<<< orphan*/ ) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inv_mpu_core_disable_regulator(struct inv_mpu6050_state *st)
{
	int result;

	result = regulator_disable(st->vddio_supply);
	if (result)
		dev_err(regmap_get_device(st->map),
			"Failed to disable regulator: %d\n", result);

	return result;
}