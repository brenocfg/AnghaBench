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
struct ww_acquire_ctx {int dummy; } ;
struct regulator {int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int regulator_get_voltage_rdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_lock_dependent (int /*<<< orphan*/ ,struct ww_acquire_ctx*) ; 
 int /*<<< orphan*/  regulator_unlock_dependent (int /*<<< orphan*/ ,struct ww_acquire_ctx*) ; 

int regulator_get_voltage(struct regulator *regulator)
{
	struct ww_acquire_ctx ww_ctx;
	int ret;

	regulator_lock_dependent(regulator->rdev, &ww_ctx);
	ret = regulator_get_voltage_rdev(regulator->rdev);
	regulator_unlock_dependent(regulator->rdev, &ww_ctx);

	return ret;
}