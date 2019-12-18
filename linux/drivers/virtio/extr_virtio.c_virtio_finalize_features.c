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
struct virtio_device {int /*<<< orphan*/  dev; TYPE_1__* config; } ;
struct TYPE_2__ {int (* finalize_features ) (struct virtio_device*) ;unsigned int (* get_status ) (struct virtio_device*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 unsigned int VIRTIO_CONFIG_S_FEATURES_OK ; 
 int /*<<< orphan*/  VIRTIO_F_VERSION_1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int stub1 (struct virtio_device*) ; 
 unsigned int stub2 (struct virtio_device*) ; 
 int /*<<< orphan*/  virtio_add_status (struct virtio_device*,unsigned int) ; 
 int /*<<< orphan*/  virtio_has_feature (struct virtio_device*,int /*<<< orphan*/ ) ; 

int virtio_finalize_features(struct virtio_device *dev)
{
	int ret = dev->config->finalize_features(dev);
	unsigned status;

	might_sleep();
	if (ret)
		return ret;

	if (!virtio_has_feature(dev, VIRTIO_F_VERSION_1))
		return 0;

	virtio_add_status(dev, VIRTIO_CONFIG_S_FEATURES_OK);
	status = dev->config->get_status(dev);
	if (!(status & VIRTIO_CONFIG_S_FEATURES_OK)) {
		dev_err(&dev->dev, "virtio: device refuses features: %x\n",
			status);
		return -ENODEV;
	}
	return 0;
}