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
struct ssb_driver {int /*<<< orphan*/  (* shutdown ) (struct ssb_device*) ;} ;
struct ssb_device {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 struct ssb_device* dev_to_ssb_dev (struct device*) ; 
 struct ssb_driver* drv_to_ssb_drv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ssb_device*) ; 

__attribute__((used)) static void ssb_device_shutdown(struct device *dev)
{
	struct ssb_device *ssb_dev = dev_to_ssb_dev(dev);
	struct ssb_driver *ssb_drv;

	if (!dev->driver)
		return;
	ssb_drv = drv_to_ssb_drv(dev->driver);
	if (ssb_drv && ssb_drv->shutdown)
		ssb_drv->shutdown(ssb_dev);
}