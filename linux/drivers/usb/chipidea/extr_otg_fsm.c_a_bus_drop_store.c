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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int a_bus_drop; int /*<<< orphan*/  lock; scalar_t__ a_bus_req; } ;
struct ci_hdrc {TYPE_1__ fsm; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ci_otg_queue_work (struct ci_hdrc*) ; 
 struct ci_hdrc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
a_bus_drop_store(struct device *dev, struct device_attribute *attr,
					const char *buf, size_t count)
{
	struct ci_hdrc	*ci = dev_get_drvdata(dev);

	if (count > 2)
		return -1;

	mutex_lock(&ci->fsm.lock);
	if (buf[0] == '0') {
		ci->fsm.a_bus_drop = 0;
	} else if (buf[0] == '1') {
		ci->fsm.a_bus_drop = 1;
		ci->fsm.a_bus_req = 0;
	}

	ci_otg_queue_work(ci);
	mutex_unlock(&ci->fsm.lock);

	return count;
}