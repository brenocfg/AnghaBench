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
struct virtio_mmio_device {TYPE_1__* pdev; } ;
struct virtio_device {int dummy; } ;
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */
 struct virtio_mmio_device* to_virtio_mmio_device (struct virtio_device*) ; 

__attribute__((used)) static const char *vm_bus_name(struct virtio_device *vdev)
{
	struct virtio_mmio_device *vm_dev = to_virtio_mmio_device(vdev);

	return vm_dev->pdev->name;
}