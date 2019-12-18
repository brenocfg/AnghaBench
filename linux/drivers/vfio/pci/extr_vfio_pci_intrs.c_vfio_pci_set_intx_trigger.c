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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct vfio_pci_device {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int EINVAL ; 
 int VFIO_IRQ_SET_DATA_BOOL ; 
 int VFIO_IRQ_SET_DATA_EVENTFD ; 
 int VFIO_IRQ_SET_DATA_NONE ; 
 scalar_t__ is_intx (struct vfio_pci_device*) ; 
 scalar_t__ is_irq_none (struct vfio_pci_device*) ; 
 int /*<<< orphan*/  vfio_intx_disable (struct vfio_pci_device*) ; 
 int vfio_intx_enable (struct vfio_pci_device*) ; 
 int vfio_intx_set_signal (struct vfio_pci_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_send_intx_eventfd (struct vfio_pci_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vfio_pci_set_intx_trigger(struct vfio_pci_device *vdev,
				     unsigned index, unsigned start,
				     unsigned count, uint32_t flags, void *data)
{
	if (is_intx(vdev) && !count && (flags & VFIO_IRQ_SET_DATA_NONE)) {
		vfio_intx_disable(vdev);
		return 0;
	}

	if (!(is_intx(vdev) || is_irq_none(vdev)) || start != 0 || count != 1)
		return -EINVAL;

	if (flags & VFIO_IRQ_SET_DATA_EVENTFD) {
		int32_t fd = *(int32_t *)data;
		int ret;

		if (is_intx(vdev))
			return vfio_intx_set_signal(vdev, fd);

		ret = vfio_intx_enable(vdev);
		if (ret)
			return ret;

		ret = vfio_intx_set_signal(vdev, fd);
		if (ret)
			vfio_intx_disable(vdev);

		return ret;
	}

	if (!is_intx(vdev))
		return -EINVAL;

	if (flags & VFIO_IRQ_SET_DATA_NONE) {
		vfio_send_intx_eventfd(vdev, NULL);
	} else if (flags & VFIO_IRQ_SET_DATA_BOOL) {
		uint8_t trigger = *(uint8_t *)data;
		if (trigger)
			vfio_send_intx_eventfd(vdev, NULL);
	}
	return 0;
}