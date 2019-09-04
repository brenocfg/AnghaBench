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
struct scmi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  scmi_handle_get (int /*<<< orphan*/ *) ; 

void scmi_set_handle(struct scmi_device *scmi_dev)
{
	scmi_dev->handle = scmi_handle_get(&scmi_dev->dev);
}