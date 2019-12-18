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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct vfio_pci_device {TYPE_1__* ctx; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  unmask; } ;

/* Variables and functions */
 int EINVAL ; 
 int VFIO_IRQ_SET_DATA_BOOL ; 
 int VFIO_IRQ_SET_DATA_EVENTFD ; 
 int VFIO_IRQ_SET_DATA_NONE ; 
 int /*<<< orphan*/  is_intx (struct vfio_pci_device*) ; 
 int /*<<< orphan*/  vfio_pci_intx_unmask (struct vfio_pci_device*) ; 
 int /*<<< orphan*/  vfio_pci_intx_unmask_handler ; 
 int /*<<< orphan*/  vfio_send_intx_eventfd ; 
 int /*<<< orphan*/  vfio_virqfd_disable (int /*<<< orphan*/ *) ; 
 int vfio_virqfd_enable (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int vfio_pci_set_intx_unmask(struct vfio_pci_device *vdev,
				    unsigned index, unsigned start,
				    unsigned count, uint32_t flags, void *data)
{
	if (!is_intx(vdev) || start != 0 || count != 1)
		return -EINVAL;

	if (flags & VFIO_IRQ_SET_DATA_NONE) {
		vfio_pci_intx_unmask(vdev);
	} else if (flags & VFIO_IRQ_SET_DATA_BOOL) {
		uint8_t unmask = *(uint8_t *)data;
		if (unmask)
			vfio_pci_intx_unmask(vdev);
	} else if (flags & VFIO_IRQ_SET_DATA_EVENTFD) {
		int32_t fd = *(int32_t *)data;
		if (fd >= 0)
			return vfio_virqfd_enable((void *) vdev,
						  vfio_pci_intx_unmask_handler,
						  vfio_send_intx_eventfd, NULL,
						  &vdev->ctx[0].unmask, fd);

		vfio_virqfd_disable(&vdev->ctx[0].unmask);
	}

	return 0;
}