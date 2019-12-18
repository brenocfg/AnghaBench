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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm2835_camera ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_cdev ; 
 int /*<<< orphan*/  vchiq_class ; 
 int /*<<< orphan*/  vchiq_debugfs_deinit () ; 
 int /*<<< orphan*/  vchiq_devid ; 

__attribute__((used)) static int vchiq_remove(struct platform_device *pdev)
{
	platform_device_unregister(bcm2835_camera);
	vchiq_debugfs_deinit();
	device_destroy(vchiq_class, vchiq_devid);
	cdev_del(&vchiq_cdev);

	return 0;
}