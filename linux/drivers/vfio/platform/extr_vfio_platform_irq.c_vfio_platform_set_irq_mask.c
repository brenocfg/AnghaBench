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
struct vfio_platform_device {TYPE_1__* irqs; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int VFIO_IRQ_INFO_MASKABLE ; 
 int VFIO_IRQ_SET_DATA_BOOL ; 
 int VFIO_IRQ_SET_DATA_EVENTFD ; 
 int VFIO_IRQ_SET_DATA_NONE ; 
 int /*<<< orphan*/  vfio_platform_mask (TYPE_1__*) ; 
 int /*<<< orphan*/  vfio_platform_mask_handler ; 
 int /*<<< orphan*/  vfio_virqfd_disable (int /*<<< orphan*/ *) ; 
 int vfio_virqfd_enable (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int vfio_platform_set_irq_mask(struct vfio_platform_device *vdev,
				      unsigned index, unsigned start,
				      unsigned count, uint32_t flags,
				      void *data)
{
	if (start != 0 || count != 1)
		return -EINVAL;

	if (!(vdev->irqs[index].flags & VFIO_IRQ_INFO_MASKABLE))
		return -EINVAL;

	if (flags & VFIO_IRQ_SET_DATA_EVENTFD) {
		int32_t fd = *(int32_t *)data;

		if (fd >= 0)
			return vfio_virqfd_enable((void *) &vdev->irqs[index],
						  vfio_platform_mask_handler,
						  NULL, NULL,
						  &vdev->irqs[index].mask, fd);

		vfio_virqfd_disable(&vdev->irqs[index].mask);
		return 0;
	}

	if (flags & VFIO_IRQ_SET_DATA_NONE) {
		vfio_platform_mask(&vdev->irqs[index]);

	} else if (flags & VFIO_IRQ_SET_DATA_BOOL) {
		uint8_t mask = *(uint8_t *)data;

		if (mask)
			vfio_platform_mask(&vdev->irqs[index]);
	}

	return 0;
}