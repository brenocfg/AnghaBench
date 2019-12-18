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
struct mei_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus_rescan_work; scalar_t__ reset_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEI_DEV_ENABLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mei_set_devstate (struct mei_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_request_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void mei_host_client_init(struct mei_device *dev)
{
	mei_set_devstate(dev, MEI_DEV_ENABLED);
	dev->reset_count = 0;

	schedule_work(&dev->bus_rescan_work);

	pm_runtime_mark_last_busy(dev->dev);
	dev_dbg(dev->dev, "rpm: autosuspend\n");
	pm_request_autosuspend(dev->dev);
}