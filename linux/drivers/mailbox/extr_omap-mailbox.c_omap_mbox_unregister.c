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
struct omap_mbox_device {struct omap_mbox** mboxes; int /*<<< orphan*/  elem; } ;
struct omap_mbox {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_mbox_devices_lock ; 

__attribute__((used)) static int omap_mbox_unregister(struct omap_mbox_device *mdev)
{
	int i;
	struct omap_mbox **mboxes;

	if (!mdev || !mdev->mboxes)
		return -EINVAL;

	mutex_lock(&omap_mbox_devices_lock);
	list_del(&mdev->elem);
	mutex_unlock(&omap_mbox_devices_lock);

	mboxes = mdev->mboxes;
	for (i = 0; mboxes[i]; i++)
		device_unregister(mboxes[i]->dev);
	return 0;
}