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
struct macio_driver {int (* resume ) (struct macio_dev*) ;} ;
struct macio_dev {int dummy; } ;
struct device {scalar_t__ driver; } ;

/* Variables and functions */
 int stub1 (struct macio_dev*) ; 
 struct macio_dev* to_macio_device (struct device*) ; 
 struct macio_driver* to_macio_driver (scalar_t__) ; 

__attribute__((used)) static int macio_device_resume(struct device * dev)
{
	struct macio_dev * macio_dev = to_macio_device(dev);
	struct macio_driver * drv = to_macio_driver(dev->driver);

	if (dev->driver && drv->resume)
		return drv->resume(macio_dev);
	return 0;
}