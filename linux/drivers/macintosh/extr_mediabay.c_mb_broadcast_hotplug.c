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
struct media_bay_info {int content_id; int /*<<< orphan*/  state; } ;
struct macio_driver {int /*<<< orphan*/  (* mediabay_event ) (struct macio_dev*,int) ;} ;
struct macio_dev {int dummy; } ;
struct device {scalar_t__ driver; int /*<<< orphan*/ * bus; } ;

/* Variables and functions */
 int MB_FD ; 
 int MB_FD1 ; 
 int MB_NO ; 
 int /*<<< orphan*/  macio_bus_type ; 
 int /*<<< orphan*/  mb_up ; 
 int /*<<< orphan*/  stub1 (struct macio_dev*,int) ; 
 struct macio_dev* to_macio_device (struct device*) ; 
 struct macio_driver* to_macio_driver (scalar_t__) ; 

__attribute__((used)) static int mb_broadcast_hotplug(struct device *dev, void *data)
{
	struct media_bay_info* bay = data;
	struct macio_dev *mdev;
	struct macio_driver *drv;
	int state;

	if (dev->bus != &macio_bus_type)
		return 0;

	state = bay->state == mb_up ? bay->content_id : MB_NO;
	if (state == MB_FD1)
		state = MB_FD;
	mdev = to_macio_device(dev);
	drv = to_macio_driver(dev->driver);
	if (dev->driver && drv->mediabay_event)
		drv->mediabay_event(mdev, state);
	return 0;
}