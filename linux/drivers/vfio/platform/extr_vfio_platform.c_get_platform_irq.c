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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int platform_get_irq (struct platform_device*,int) ; 

__attribute__((used)) static int get_platform_irq(struct vfio_platform_device *vdev, int i)
{
	struct platform_device *pdev = (struct platform_device *) vdev->opaque;

	return platform_get_irq(pdev, i);
}