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
struct scmi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  id; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scmi_bus_id ; 
 int /*<<< orphan*/  scmi_handle_put (int /*<<< orphan*/ ) ; 

void scmi_device_destroy(struct scmi_device *scmi_dev)
{
	scmi_handle_put(scmi_dev->handle);
	ida_simple_remove(&scmi_bus_id, scmi_dev->id);
	device_unregister(&scmi_dev->dev);
}