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
struct virtio_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct virtio_device* dev_to_virtio (struct device*) ; 
 int /*<<< orphan*/  unregister_virtio_device (struct virtio_device*) ; 

int rproc_remove_virtio_dev(struct device *dev, void *data)
{
	struct virtio_device *vdev = dev_to_virtio(dev);

	unregister_virtio_device(vdev);
	return 0;
}