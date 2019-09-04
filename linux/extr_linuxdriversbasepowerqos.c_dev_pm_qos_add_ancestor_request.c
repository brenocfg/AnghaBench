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
struct TYPE_2__ {int /*<<< orphan*/  set_latency_tolerance; int /*<<< orphan*/  ignore_children; } ;
struct device {struct device* parent; TYPE_1__ power; } ;
struct dev_pm_qos_request {int /*<<< orphan*/ * dev; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  enum dev_pm_qos_req_type { ____Placeholder_dev_pm_qos_req_type } dev_pm_qos_req_type ;

/* Variables and functions */
#define  DEV_PM_QOS_LATENCY_TOLERANCE 129 
#define  DEV_PM_QOS_RESUME_LATENCY 128 
 int ENODEV ; 
 int dev_pm_qos_add_request (struct device*,struct dev_pm_qos_request*,int,int /*<<< orphan*/ ) ; 

int dev_pm_qos_add_ancestor_request(struct device *dev,
				    struct dev_pm_qos_request *req,
				    enum dev_pm_qos_req_type type, s32 value)
{
	struct device *ancestor = dev->parent;
	int ret = -ENODEV;

	switch (type) {
	case DEV_PM_QOS_RESUME_LATENCY:
		while (ancestor && !ancestor->power.ignore_children)
			ancestor = ancestor->parent;

		break;
	case DEV_PM_QOS_LATENCY_TOLERANCE:
		while (ancestor && !ancestor->power.set_latency_tolerance)
			ancestor = ancestor->parent;

		break;
	default:
		ancestor = NULL;
	}
	if (ancestor)
		ret = dev_pm_qos_add_request(ancestor, req, type, value);

	if (ret < 0)
		req->dev = NULL;

	return ret;
}