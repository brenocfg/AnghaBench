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
struct vfio_platform_device {scalar_t__ opaque; } ;
struct amba_device {int* irq; } ;

/* Variables and functions */
 int AMBA_NR_IRQS ; 
 int ENXIO ; 

__attribute__((used)) static int get_amba_irq(struct vfio_platform_device *vdev, int i)
{
	struct amba_device *adev = (struct amba_device *) vdev->opaque;
	int ret = 0;

	if (i < AMBA_NR_IRQS)
		ret = adev->irq[i];

	/* zero is an unset IRQ for AMBA devices */
	return ret ? ret : -ENXIO;
}