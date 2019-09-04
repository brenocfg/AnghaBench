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
struct mei_device {scalar_t__ dev_state; int /*<<< orphan*/  write_waiting_list; int /*<<< orphan*/  write_list; int /*<<< orphan*/  ctrl_wr_list; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MEI_DEV_ENABLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mei_dev_state_str (scalar_t__) ; 

bool mei_write_is_idle(struct mei_device *dev)
{
	bool idle = (dev->dev_state == MEI_DEV_ENABLED &&
		list_empty(&dev->ctrl_wr_list) &&
		list_empty(&dev->write_list)   &&
		list_empty(&dev->write_waiting_list));

	dev_dbg(dev->dev, "write pg: is idle[%d] state=%s ctrl=%01d write=%01d wwait=%01d\n",
		idle,
		mei_dev_state_str(dev->dev_state),
		list_empty(&dev->ctrl_wr_list),
		list_empty(&dev->write_list),
		list_empty(&dev->write_waiting_list));

	return idle;
}