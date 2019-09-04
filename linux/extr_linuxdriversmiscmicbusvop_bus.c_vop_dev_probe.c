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
struct vop_driver {int (* probe ) (struct vop_device*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct vop_device {TYPE_1__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct vop_device* dev_to_vop (struct device*) ; 
 struct vop_driver* drv_to_vop (int /*<<< orphan*/ ) ; 
 int stub1 (struct vop_device*) ; 

__attribute__((used)) static int vop_dev_probe(struct device *d)
{
	struct vop_device *dev = dev_to_vop(d);
	struct vop_driver *drv = drv_to_vop(dev->dev.driver);

	return drv->probe(dev);
}