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
struct ccw_device {TYPE_1__* private; } ;
struct TYPE_2__ {scalar_t__ pgid_reset_mask; scalar_t__ path_new_mask; scalar_t__ path_gone_mask; } ;

/* Variables and functions */

__attribute__((used)) static void ccw_device_reset_path_events(struct ccw_device *cdev)
{
	cdev->private->path_gone_mask = 0;
	cdev->private->path_new_mask = 0;
	cdev->private->pgid_reset_mask = 0;
}