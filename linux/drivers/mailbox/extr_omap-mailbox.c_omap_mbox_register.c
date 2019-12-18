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
struct omap_mbox_device {int /*<<< orphan*/  controller; int /*<<< orphan*/  dev; int /*<<< orphan*/  elem; struct omap_mbox** mboxes; } ;
struct omap_mbox {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct omap_mbox*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ ) ; 
 int devm_mbox_controller_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_mbox_class ; 
 int /*<<< orphan*/  omap_mbox_devices ; 
 int /*<<< orphan*/  omap_mbox_devices_lock ; 

__attribute__((used)) static int omap_mbox_register(struct omap_mbox_device *mdev)
{
	int ret;
	int i;
	struct omap_mbox **mboxes;

	if (!mdev || !mdev->mboxes)
		return -EINVAL;

	mboxes = mdev->mboxes;
	for (i = 0; mboxes[i]; i++) {
		struct omap_mbox *mbox = mboxes[i];

		mbox->dev = device_create(&omap_mbox_class, mdev->dev,
					0, mbox, "%s", mbox->name);
		if (IS_ERR(mbox->dev)) {
			ret = PTR_ERR(mbox->dev);
			goto err_out;
		}
	}

	mutex_lock(&omap_mbox_devices_lock);
	list_add(&mdev->elem, &omap_mbox_devices);
	mutex_unlock(&omap_mbox_devices_lock);

	ret = devm_mbox_controller_register(mdev->dev, &mdev->controller);

err_out:
	if (ret) {
		while (i--)
			device_unregister(mboxes[i]->dev);
	}
	return ret;
}