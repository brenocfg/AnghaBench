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
struct regulator {int /*<<< orphan*/  rdev; scalar_t__ always_on; } ;

/* Variables and functions */
 int _regulator_is_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_unlock (int /*<<< orphan*/ ) ; 

int regulator_is_enabled(struct regulator *regulator)
{
	int ret;

	if (regulator->always_on)
		return 1;

	regulator_lock(regulator->rdev);
	ret = _regulator_is_enabled(regulator->rdev);
	regulator_unlock(regulator->rdev);

	return ret;
}