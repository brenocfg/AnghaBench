#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct virtio_driver {int /*<<< orphan*/  (* remove ) (struct virtio_device*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  driver; } ;
struct virtio_device {TYPE_2__* config; TYPE_1__ dev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_status ) (struct virtio_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_CONFIG_S_ACKNOWLEDGE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 struct virtio_device* dev_to_virtio (struct device*) ; 
 struct virtio_driver* drv_to_virtio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct virtio_device*) ; 
 int /*<<< orphan*/  stub2 (struct virtio_device*) ; 
 int /*<<< orphan*/  virtio_add_status (struct virtio_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_config_disable (struct virtio_device*) ; 

__attribute__((used)) static int virtio_dev_remove(struct device *_d)
{
	struct virtio_device *dev = dev_to_virtio(_d);
	struct virtio_driver *drv = drv_to_virtio(dev->dev.driver);

	virtio_config_disable(dev);

	drv->remove(dev);

	/* Driver should have reset device. */
	WARN_ON_ONCE(dev->config->get_status(dev));

	/* Acknowledge the device's existence again. */
	virtio_add_status(dev, VIRTIO_CONFIG_S_ACKNOWLEDGE);
	return 0;
}