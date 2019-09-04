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
struct saa7134_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void saa7134_unregister_media_device(struct saa7134_dev *dev)
{

#ifdef CONFIG_MEDIA_CONTROLLER
	if (!dev->media_dev)
		return;
	media_device_unregister(dev->media_dev);
	media_device_cleanup(dev->media_dev);
	kfree(dev->media_dev);
	dev->media_dev = NULL;
#endif
}