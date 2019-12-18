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
struct ubi_notification {int /*<<< orphan*/  vi; int /*<<< orphan*/  di; } ;
struct ubi_device {int vtbl_slots; int /*<<< orphan*/  device_mutex; int /*<<< orphan*/ * volumes; } ;
struct notifier_block {int /*<<< orphan*/  (* notifier_call ) (struct notifier_block*,int,struct ubi_notification*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int,struct ubi_notification*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct notifier_block*,int,struct ubi_notification*) ; 
 int /*<<< orphan*/  ubi_do_get_device_info (struct ubi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_do_get_volume_info (struct ubi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_notifiers ; 

int ubi_notify_all(struct ubi_device *ubi, int ntype, struct notifier_block *nb)
{
	struct ubi_notification nt;
	int i, count = 0;

	ubi_do_get_device_info(ubi, &nt.di);

	mutex_lock(&ubi->device_mutex);
	for (i = 0; i < ubi->vtbl_slots; i++) {
		/*
		 * Since the @ubi->device is locked, and we are not going to
		 * change @ubi->volumes, we do not have to lock
		 * @ubi->volumes_lock.
		 */
		if (!ubi->volumes[i])
			continue;

		ubi_do_get_volume_info(ubi, ubi->volumes[i], &nt.vi);
		if (nb)
			nb->notifier_call(nb, ntype, &nt);
		else
			blocking_notifier_call_chain(&ubi_notifiers, ntype,
						     &nt);
		count += 1;
	}
	mutex_unlock(&ubi->device_mutex);

	return count;
}