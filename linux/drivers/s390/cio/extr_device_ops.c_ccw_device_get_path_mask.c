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
struct subchannel {int /*<<< orphan*/  lpm; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_1__ dev; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

__u8 ccw_device_get_path_mask(struct ccw_device *cdev)
{
	struct subchannel *sch;

	if (!cdev->dev.parent)
		return 0;

	sch = to_subchannel(cdev->dev.parent);
	return sch->lpm;
}