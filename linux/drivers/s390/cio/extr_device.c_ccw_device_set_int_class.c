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
struct ccw_driver {scalar_t__ int_class; } ;
struct ccw_device {TYPE_1__* private; struct ccw_driver* drv; } ;
struct TYPE_2__ {scalar_t__ int_class; } ;

/* Variables and functions */
 scalar_t__ IRQIO_CIO ; 

__attribute__((used)) static void ccw_device_set_int_class(struct ccw_device *cdev)
{
	struct ccw_driver *cdrv = cdev->drv;

	/* Note: we interpret class 0 in this context as an uninitialized
	 * field since it translates to a non-I/O interrupt class. */
	if (cdrv->int_class != 0)
		cdev->private->int_class = cdrv->int_class;
	else
		cdev->private->int_class = IRQIO_CIO;
}