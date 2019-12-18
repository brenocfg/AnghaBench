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
struct ubi_device {int dummy; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int UBI_MAX_DEVICES ; 
 int /*<<< orphan*/  UBI_VOLUME_ADDED ; 
 struct ubi_device** ubi_devices ; 
 scalar_t__ ubi_notify_all (struct ubi_device*,int /*<<< orphan*/ ,struct notifier_block*) ; 

int ubi_enumerate_volumes(struct notifier_block *nb)
{
	int i, count = 0;

	/*
	 * Since the @ubi_devices_mutex is locked, and we are not going to
	 * change @ubi_devices, we do not have to lock @ubi_devices_lock.
	 */
	for (i = 0; i < UBI_MAX_DEVICES; i++) {
		struct ubi_device *ubi = ubi_devices[i];

		if (!ubi)
			continue;
		count += ubi_notify_all(ubi, UBI_VOLUME_ADDED, nb);
	}

	return count;
}