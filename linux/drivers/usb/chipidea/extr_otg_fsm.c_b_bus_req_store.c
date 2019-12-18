#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int b_bus_req; int /*<<< orphan*/  lock; TYPE_1__* otg; } ;
struct TYPE_5__ {int host_request_flag; } ;
struct ci_hdrc {TYPE_3__ fsm; TYPE_2__ gadget; } ;
typedef  int ssize_t ;
struct TYPE_4__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ OTG_STATE_B_PERIPHERAL ; 
 int /*<<< orphan*/  ci_otg_queue_work (struct ci_hdrc*) ; 
 struct ci_hdrc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
b_bus_req_store(struct device *dev, struct device_attribute *attr,
					const char *buf, size_t count)
{
	struct ci_hdrc	*ci = dev_get_drvdata(dev);

	if (count > 2)
		return -1;

	mutex_lock(&ci->fsm.lock);
	if (buf[0] == '0')
		ci->fsm.b_bus_req = 0;
	else if (buf[0] == '1') {
		ci->fsm.b_bus_req = 1;
		if (ci->fsm.otg->state == OTG_STATE_B_PERIPHERAL) {
			ci->gadget.host_request_flag = 1;
			mutex_unlock(&ci->fsm.lock);
			return count;
		}
	}

	ci_otg_queue_work(ci);
	mutex_unlock(&ci->fsm.lock);

	return count;
}