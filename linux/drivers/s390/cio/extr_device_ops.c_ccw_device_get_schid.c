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
struct subchannel_id {int dummy; } ;
struct subchannel {struct subchannel_id schid; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_1__ dev; } ;

/* Variables and functions */
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

void ccw_device_get_schid(struct ccw_device *cdev, struct subchannel_id *schid)
{
	struct subchannel *sch = to_subchannel(cdev->dev.parent);

	*schid = sch->schid;
}