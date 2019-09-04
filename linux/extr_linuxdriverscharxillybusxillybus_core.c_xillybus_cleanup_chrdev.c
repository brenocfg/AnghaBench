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
struct xilly_endpoint {int lowest_minor; int num_channels; int /*<<< orphan*/  dev; int /*<<< orphan*/  major; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xillybus_class ; 

__attribute__((used)) static void xillybus_cleanup_chrdev(struct xilly_endpoint *endpoint)
{
	int minor;

	for (minor = endpoint->lowest_minor;
	     minor < (endpoint->lowest_minor + endpoint->num_channels);
	     minor++)
		device_destroy(xillybus_class, MKDEV(endpoint->major, minor));
	cdev_del(&endpoint->cdev);
	unregister_chrdev_region(MKDEV(endpoint->major,
				       endpoint->lowest_minor),
				 endpoint->num_channels);

	dev_info(endpoint->dev, "Removed %d device files.\n",
		 endpoint->num_channels);
}