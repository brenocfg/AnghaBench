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
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct regulator_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  list; int /*<<< orphan*/  open_count; int /*<<< orphan*/  debugfs; TYPE_1__ disable_work; scalar_t__ supply; int /*<<< orphan*/  use_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int /*<<< orphan*/  regulator_ena_gpio_free (struct regulator_dev*) ; 
 int /*<<< orphan*/  regulator_list_mutex ; 
 int /*<<< orphan*/  regulator_put (scalar_t__) ; 
 int /*<<< orphan*/  regulator_remove_coupling (struct regulator_dev*) ; 
 int /*<<< orphan*/  unset_regulator_supplies (struct regulator_dev*) ; 

void regulator_unregister(struct regulator_dev *rdev)
{
	if (rdev == NULL)
		return;

	if (rdev->supply) {
		while (rdev->use_count--)
			regulator_disable(rdev->supply);
		regulator_put(rdev->supply);
	}

	flush_work(&rdev->disable_work.work);

	mutex_lock(&regulator_list_mutex);

	debugfs_remove_recursive(rdev->debugfs);
	WARN_ON(rdev->open_count);
	regulator_remove_coupling(rdev);
	unset_regulator_supplies(rdev);
	list_del(&rdev->list);
	regulator_ena_gpio_free(rdev);
	device_unregister(&rdev->dev);

	mutex_unlock(&regulator_list_mutex);
}