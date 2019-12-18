#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vfio_ap_queue {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* vfio_ap_drv; } ;
struct TYPE_3__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 struct vfio_ap_queue* dev_get_drvdata (struct device*) ; 
 struct device* driver_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_apqn ; 
 TYPE_2__* matrix_dev ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  vfio_ap_irq_disable (struct vfio_ap_queue*) ; 

__attribute__((used)) static void vfio_ap_irq_disable_apqn(int apqn)
{
	struct device *dev;
	struct vfio_ap_queue *q;

	dev = driver_find_device(&matrix_dev->vfio_ap_drv->driver, NULL,
				 &apqn, match_apqn);
	if (dev) {
		q = dev_get_drvdata(dev);
		vfio_ap_irq_disable(q);
		put_device(dev);
	}
}