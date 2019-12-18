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
struct maple_driver {int dummy; } ;
struct maple_device {struct maple_driver* driver; int /*<<< orphan*/  fileerr_handler; int /*<<< orphan*/  can_unload; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 struct maple_device* to_maple_dev (struct device*) ; 
 struct maple_driver* to_maple_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmu_can_unload ; 
 int vmu_connect (struct maple_device*) ; 
 int /*<<< orphan*/  vmu_file_error ; 

__attribute__((used)) static int probe_maple_vmu(struct device *dev)
{
	int error;
	struct maple_device *mdev = to_maple_dev(dev);
	struct maple_driver *mdrv = to_maple_driver(dev->driver);

	mdev->can_unload = vmu_can_unload;
	mdev->fileerr_handler = vmu_file_error;
	mdev->driver = mdrv;

	error = vmu_connect(mdev);
	if (error)
		return error;

	return 0;
}