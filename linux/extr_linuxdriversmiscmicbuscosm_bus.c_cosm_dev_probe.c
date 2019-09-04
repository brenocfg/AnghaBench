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
struct device {int dummy; } ;
struct cosm_driver {int (* probe ) (struct cosm_device*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct cosm_device {TYPE_1__ dev; } ;

/* Variables and functions */
 struct cosm_device* dev_to_cosm (struct device*) ; 
 struct cosm_driver* drv_to_cosm (int /*<<< orphan*/ ) ; 
 int stub1 (struct cosm_device*) ; 

__attribute__((used)) static int cosm_dev_probe(struct device *d)
{
	struct cosm_device *dev = dev_to_cosm(d);
	struct cosm_driver *drv = drv_to_cosm(dev->dev.driver);

	return drv->probe(dev);
}