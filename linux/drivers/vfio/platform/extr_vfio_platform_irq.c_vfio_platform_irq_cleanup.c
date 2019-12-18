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
struct vfio_platform_device {int num_irqs; int /*<<< orphan*/  irqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_set_trigger (struct vfio_platform_device*,int,int,int /*<<< orphan*/ *) ; 

void vfio_platform_irq_cleanup(struct vfio_platform_device *vdev)
{
	int i;

	for (i = 0; i < vdev->num_irqs; i++)
		vfio_set_trigger(vdev, i, -1, NULL);

	vdev->num_irqs = 0;
	kfree(vdev->irqs);
}