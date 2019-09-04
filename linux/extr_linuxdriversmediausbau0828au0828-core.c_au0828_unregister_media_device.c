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
struct au0828_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void au0828_unregister_media_device(struct au0828_dev *dev)
{
#ifdef CONFIG_MEDIA_CONTROLLER
	struct media_device *mdev = dev->media_dev;
	struct media_entity_notify *notify, *nextp;

	if (!mdev || !media_devnode_is_registered(mdev->devnode))
		return;

	/* Remove au0828 entity_notify callbacks */
	list_for_each_entry_safe(notify, nextp, &mdev->entity_notify, list) {
		if (notify->notify != au0828_media_graph_notify)
			continue;
		media_device_unregister_entity_notify(mdev, notify);
	}

	/* clear enable_source, disable_source */
	mutex_lock(&mdev->graph_mutex);
	dev->media_dev->source_priv = NULL;
	dev->media_dev->enable_source = NULL;
	dev->media_dev->disable_source = NULL;
	mutex_unlock(&mdev->graph_mutex);

	media_device_unregister(dev->media_dev);
	media_device_cleanup(dev->media_dev);
	kfree(dev->media_dev);
	dev->media_dev = NULL;
#endif
}