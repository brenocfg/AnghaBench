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
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct regulator_dev {TYPE_1__ mutex; } ;
struct regulator {int enable_count; scalar_t__ uA_load; struct regulator_dev* rdev; } ;

/* Variables and functions */
 int drms_uA_update (struct regulator_dev*) ; 
 int /*<<< orphan*/  lockdep_assert_held_once (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _regulator_handle_consumer_enable(struct regulator *regulator)
{
	struct regulator_dev *rdev = regulator->rdev;

	lockdep_assert_held_once(&rdev->mutex.base);

	regulator->enable_count++;
	if (regulator->uA_load && regulator->enable_count == 1)
		return drms_uA_update(rdev);

	return 0;
}