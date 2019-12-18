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
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int __disable_cmf (struct ccw_device*) ; 
 int /*<<< orphan*/  device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unlock (int /*<<< orphan*/ *) ; 

int disable_cmf(struct ccw_device *cdev)
{
	int ret;

	device_lock(&cdev->dev);
	ret = __disable_cmf(cdev);
	device_unlock(&cdev->dev);

	return ret;
}