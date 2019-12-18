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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int blocking_notifier_chain_register (int /*<<< orphan*/ *,struct notifier_block*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_devices_mutex ; 
 int /*<<< orphan*/  ubi_enumerate_volumes (struct notifier_block*) ; 
 int /*<<< orphan*/  ubi_notifiers ; 

int ubi_register_volume_notifier(struct notifier_block *nb,
				 int ignore_existing)
{
	int err;

	err = blocking_notifier_chain_register(&ubi_notifiers, nb);
	if (err != 0)
		return err;
	if (ignore_existing)
		return 0;

	/*
	 * We are going to walk all UBI devices and all volumes, and
	 * notify the user about existing volumes by the %UBI_VOLUME_ADDED
	 * event. We have to lock the @ubi_devices_mutex to make sure UBI
	 * devices do not disappear.
	 */
	mutex_lock(&ubi_devices_mutex);
	ubi_enumerate_volumes(nb);
	mutex_unlock(&ubi_devices_mutex);

	return err;
}