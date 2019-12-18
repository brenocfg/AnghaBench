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
typedef  int u8 ;
struct virtio_mmio_device {scalar_t__ base; } ;
struct virtio_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ VIRTIO_MMIO_STATUS ; 
 int readl (scalar_t__) ; 
 struct virtio_mmio_device* to_virtio_mmio_device (struct virtio_device*) ; 

__attribute__((used)) static u8 vm_get_status(struct virtio_device *vdev)
{
	struct virtio_mmio_device *vm_dev = to_virtio_mmio_device(vdev);

	return readl(vm_dev->base + VIRTIO_MMIO_STATUS) & 0xff;
}