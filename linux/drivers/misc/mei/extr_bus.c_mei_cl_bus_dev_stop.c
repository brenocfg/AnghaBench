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
struct mei_cl_device {int /*<<< orphan*/  dev; scalar_t__ is_added; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_release_driver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mei_cl_bus_dev_stop(struct mei_cl_device *cldev)
{
	if (cldev->is_added)
		device_release_driver(&cldev->dev);
}