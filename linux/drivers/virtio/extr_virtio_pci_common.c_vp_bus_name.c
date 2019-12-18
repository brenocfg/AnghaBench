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
struct virtio_pci_device {int /*<<< orphan*/  pci_dev; } ;
struct virtio_device {int dummy; } ;

/* Variables and functions */
 char const* pci_name (int /*<<< orphan*/ ) ; 
 struct virtio_pci_device* to_vp_device (struct virtio_device*) ; 

const char *vp_bus_name(struct virtio_device *vdev)
{
	struct virtio_pci_device *vp_dev = to_vp_device(vdev);

	return pci_name(vp_dev->pci_dev);
}