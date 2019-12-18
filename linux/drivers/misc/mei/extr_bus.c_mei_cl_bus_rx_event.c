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
struct mei_cl_device {int /*<<< orphan*/  rx_work; int /*<<< orphan*/  rx_cb; } ;
struct mei_cl {struct mei_cl_device* cldev; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

bool mei_cl_bus_rx_event(struct mei_cl *cl)
{
	struct mei_cl_device *cldev = cl->cldev;

	if (!cldev || !cldev->rx_cb)
		return false;

	schedule_work(&cldev->rx_work);

	return true;
}