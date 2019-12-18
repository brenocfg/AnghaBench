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
struct device {int dummy; } ;
struct ccw_device {TYPE_1__* private; } ;
struct ccw_dev_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_id; } ;

/* Variables and functions */
 int ccw_dev_id_is_equal (int /*<<< orphan*/ *,struct ccw_dev_id*) ; 
 struct ccw_device* to_ccwdev (struct device*) ; 

__attribute__((used)) static int match_dev_id(struct device *dev, const void *data)
{
	struct ccw_device *cdev = to_ccwdev(dev);
	struct ccw_dev_id *dev_id = (void *)data;

	return ccw_dev_id_is_equal(&cdev->private->dev_id, dev_id);
}