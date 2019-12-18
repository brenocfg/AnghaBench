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
typedef  int u16 ;
struct urdev {int dummy; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct ccw_device* get_ccwdev_by_busid (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  ur_driver ; 
 struct urdev* urdev_get_from_cdev (struct ccw_device*) ; 

__attribute__((used)) static struct urdev *urdev_get_from_devno(u16 devno)
{
	char bus_id[16];
	struct ccw_device *cdev;
	struct urdev *urd;

	sprintf(bus_id, "0.0.%04x", devno);
	cdev = get_ccwdev_by_busid(&ur_driver, bus_id);
	if (!cdev)
		return NULL;
	urd = urdev_get_from_cdev(cdev);
	put_device(&cdev->dev);
	return urd;
}