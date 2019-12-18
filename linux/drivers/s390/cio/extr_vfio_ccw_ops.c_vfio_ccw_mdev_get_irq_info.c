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
struct vfio_irq_info {scalar_t__ index; int count; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ VFIO_CCW_IO_IRQ_INDEX ; 
 int /*<<< orphan*/  VFIO_IRQ_INFO_EVENTFD ; 

__attribute__((used)) static int vfio_ccw_mdev_get_irq_info(struct vfio_irq_info *info)
{
	if (info->index != VFIO_CCW_IO_IRQ_INDEX)
		return -EINVAL;

	info->count = 1;
	info->flags = VFIO_IRQ_INFO_EVENTFD;

	return 0;
}