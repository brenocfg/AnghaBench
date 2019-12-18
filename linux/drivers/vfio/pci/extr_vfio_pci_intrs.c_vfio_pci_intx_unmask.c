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
struct vfio_pci_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ vfio_pci_intx_unmask_handler (struct vfio_pci_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfio_send_intx_eventfd (struct vfio_pci_device*,int /*<<< orphan*/ *) ; 

void vfio_pci_intx_unmask(struct vfio_pci_device *vdev)
{
	if (vfio_pci_intx_unmask_handler(vdev, NULL) > 0)
		vfio_send_intx_eventfd(vdev, NULL);
}