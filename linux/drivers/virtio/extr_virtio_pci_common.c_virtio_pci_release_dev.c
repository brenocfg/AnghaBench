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
struct virtio_pci_device {int dummy; } ;
struct virtio_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct virtio_device* dev_to_virtio (struct device*) ; 
 int /*<<< orphan*/  kfree (struct virtio_pci_device*) ; 
 struct virtio_pci_device* to_vp_device (struct virtio_device*) ; 

__attribute__((used)) static void virtio_pci_release_dev(struct device *_d)
{
	struct virtio_device *vdev = dev_to_virtio(_d);
	struct virtio_pci_device *vp_dev = to_vp_device(vdev);

	/* As struct device is a kobject, it's not safe to
	 * free the memory (including the reference counter itself)
	 * until it's release callback. */
	kfree(vp_dev);
}