#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct regulator_dev {int /*<<< orphan*/  owner; TYPE_1__ dev; scalar_t__ exclusive; int /*<<< orphan*/  open_count; } ;
struct regulator {int /*<<< orphan*/  supply_name; int /*<<< orphan*/  list; scalar_t__ dev; int /*<<< orphan*/  debugfs; struct regulator_dev* rdev; int /*<<< orphan*/  enable_count; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct regulator*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_link_remove (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct regulator*) ; 
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held_once (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  regulator_list_mutex ; 
 int /*<<< orphan*/  regulator_lock (struct regulator_dev*) ; 
 int /*<<< orphan*/  regulator_unlock (struct regulator_dev*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _regulator_put(struct regulator *regulator)
{
	struct regulator_dev *rdev;

	if (IS_ERR_OR_NULL(regulator))
		return;

	lockdep_assert_held_once(&regulator_list_mutex);

	/* Docs say you must disable before calling regulator_put() */
	WARN_ON(regulator->enable_count);

	rdev = regulator->rdev;

	debugfs_remove_recursive(regulator->debugfs);

	if (regulator->dev) {
		device_link_remove(regulator->dev, &rdev->dev);

		/* remove any sysfs entries */
		sysfs_remove_link(&rdev->dev.kobj, regulator->supply_name);
	}

	regulator_lock(rdev);
	list_del(&regulator->list);

	rdev->open_count--;
	rdev->exclusive = 0;
	put_device(&rdev->dev);
	regulator_unlock(rdev);

	kfree_const(regulator->supply_name);
	kfree(regulator);

	module_put(rdev->owner);
}