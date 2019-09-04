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
struct ib_ucm_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  cdev; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_device_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_ucm_free_dev (struct ib_ucm_device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ib_ucm_remove_one(struct ib_device *device, void *client_data)
{
	struct ib_ucm_device *ucm_dev = client_data;

	if (!ucm_dev)
		return;

	cdev_device_del(&ucm_dev->cdev, &ucm_dev->dev);
	ib_ucm_free_dev(ucm_dev);
	put_device(&ucm_dev->dev);
}