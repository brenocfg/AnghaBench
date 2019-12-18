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
struct regulator_dev {int /*<<< orphan*/  disable_work; } ;
struct regulator {int /*<<< orphan*/  deferred_disables; struct regulator_dev* rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int regulator_disable (struct regulator*) ; 
 int /*<<< orphan*/  regulator_lock (struct regulator_dev*) ; 
 int /*<<< orphan*/  regulator_unlock (struct regulator_dev*) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

int regulator_disable_deferred(struct regulator *regulator, int ms)
{
	struct regulator_dev *rdev = regulator->rdev;

	if (!ms)
		return regulator_disable(regulator);

	regulator_lock(rdev);
	regulator->deferred_disables++;
	mod_delayed_work(system_power_efficient_wq, &rdev->disable_work,
			 msecs_to_jiffies(ms));
	regulator_unlock(rdev);

	return 0;
}