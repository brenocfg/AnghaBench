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
struct ccw_dev_id {int dummy; } ;
struct TYPE_2__ {struct ccw_dev_id dev_id; } ;

/* Variables and functions */

void ccw_device_get_id(struct ccw_device *cdev, struct ccw_dev_id *dev_id)
{
	*dev_id = cdev->private->dev_id;
}