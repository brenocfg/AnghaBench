#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct subchannel {TYPE_2__ dev; } ;
struct channel_subsystem {int /*<<< orphan*/  pseudo_subchannel; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ccw_device_move_to_sch (struct ccw_device*,int /*<<< orphan*/ ) ; 
 struct channel_subsystem* to_css (int /*<<< orphan*/ ) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccw_device_move_to_orph(struct ccw_device *cdev)
{
	struct subchannel *sch = to_subchannel(cdev->dev.parent);
	struct channel_subsystem *css = to_css(sch->dev.parent);

	return ccw_device_move_to_sch(cdev, css->pseudo_subchannel);
}