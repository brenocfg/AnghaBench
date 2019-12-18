#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mei_cl_device {int /*<<< orphan*/  dev; scalar_t__ is_added; int /*<<< orphan*/  bus_list; TYPE_1__* bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  cl_bus_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mei_cl_bus_dev_destroy(struct mei_cl_device *cldev)
{

	WARN_ON(!mutex_is_locked(&cldev->bus->cl_bus_lock));

	if (!cldev->is_added)
		return;

	device_del(&cldev->dev);

	list_del_init(&cldev->bus_list);

	cldev->is_added = 0;
	put_device(&cldev->dev);
}