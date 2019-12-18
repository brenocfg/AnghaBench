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
 int ENODEV ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int device_attach (int /*<<< orphan*/ *) ; 
 scalar_t__ device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_release_driver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ccw_device_do_unbind_bind(struct ccw_device *cdev)
{
	int ret;

	if (device_is_registered(&cdev->dev)) {
		device_release_driver(&cdev->dev);
		ret = device_attach(&cdev->dev);
		WARN_ON(ret == -ENODEV);
	}
}