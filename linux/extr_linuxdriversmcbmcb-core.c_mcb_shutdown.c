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
struct mcb_driver {int /*<<< orphan*/  (* shutdown ) (struct mcb_device*) ;} ;
struct mcb_device {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct mcb_device*) ; 
 struct mcb_device* to_mcb_device (struct device*) ; 
 struct mcb_driver* to_mcb_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mcb_shutdown(struct device *dev)
{
	struct mcb_driver *mdrv = to_mcb_driver(dev->driver);
	struct mcb_device *mdev = to_mcb_device(dev);

	if (mdrv && mdrv->shutdown)
		mdrv->shutdown(mdev);
}