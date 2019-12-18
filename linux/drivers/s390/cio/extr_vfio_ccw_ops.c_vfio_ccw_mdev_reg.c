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
struct subchannel {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int mdev_register_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfio_ccw_mdev_ops ; 

int vfio_ccw_mdev_reg(struct subchannel *sch)
{
	return mdev_register_device(&sch->dev, &vfio_ccw_mdev_ops);
}