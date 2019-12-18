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
struct vfio_platform_irq {int flags; int /*<<< orphan*/  hwirq; } ;
struct vfio_platform_device {struct vfio_platform_irq* irqs; } ;
typedef  int /*<<< orphan*/  (* irq_handler_t ) (int /*<<< orphan*/ ,struct vfio_platform_irq*) ;
typedef  int int32_t ;

/* Variables and functions */
 int EINVAL ; 
 int VFIO_IRQ_INFO_AUTOMASKED ; 
 int VFIO_IRQ_SET_DATA_BOOL ; 
 int VFIO_IRQ_SET_DATA_EVENTFD ; 
 int VFIO_IRQ_SET_DATA_NONE ; 
 int /*<<< orphan*/  vfio_automasked_irq_handler (int /*<<< orphan*/ ,struct vfio_platform_irq*) ; 
 int /*<<< orphan*/  vfio_irq_handler (int /*<<< orphan*/ ,struct vfio_platform_irq*) ; 
 int vfio_set_trigger (struct vfio_platform_device*,unsigned int,int,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,struct vfio_platform_irq*)) ; 

__attribute__((used)) static int vfio_platform_set_irq_trigger(struct vfio_platform_device *vdev,
					 unsigned index, unsigned start,
					 unsigned count, uint32_t flags,
					 void *data)
{
	struct vfio_platform_irq *irq = &vdev->irqs[index];
	irq_handler_t handler;

	if (vdev->irqs[index].flags & VFIO_IRQ_INFO_AUTOMASKED)
		handler = vfio_automasked_irq_handler;
	else
		handler = vfio_irq_handler;

	if (!count && (flags & VFIO_IRQ_SET_DATA_NONE))
		return vfio_set_trigger(vdev, index, -1, handler);

	if (start != 0 || count != 1)
		return -EINVAL;

	if (flags & VFIO_IRQ_SET_DATA_EVENTFD) {
		int32_t fd = *(int32_t *)data;

		return vfio_set_trigger(vdev, index, fd, handler);
	}

	if (flags & VFIO_IRQ_SET_DATA_NONE) {
		handler(irq->hwirq, irq);

	} else if (flags & VFIO_IRQ_SET_DATA_BOOL) {
		uint8_t trigger = *(uint8_t *)data;

		if (trigger)
			handler(irq->hwirq, irq);
	}

	return 0;
}