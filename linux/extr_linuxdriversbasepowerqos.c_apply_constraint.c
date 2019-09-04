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
struct TYPE_5__ {int /*<<< orphan*/  flr; int /*<<< orphan*/  pnode; } ;
struct dev_pm_qos_request {int type; TYPE_2__ data; TYPE_3__* dev; } ;
struct dev_pm_qos {int /*<<< orphan*/  flags; int /*<<< orphan*/  latency_tolerance; int /*<<< orphan*/  resume_latency; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  enum pm_qos_req_action { ____Placeholder_pm_qos_req_action } pm_qos_req_action ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_latency_tolerance ) (TYPE_3__*,int /*<<< orphan*/ ) ;struct dev_pm_qos* qos; } ;
struct TYPE_6__ {TYPE_1__ power; } ;

/* Variables and functions */
#define  DEV_PM_QOS_FLAGS 130 
#define  DEV_PM_QOS_LATENCY_TOLERANCE 129 
#define  DEV_PM_QOS_RESUME_LATENCY 128 
 int EINVAL ; 
 int PM_QOS_REMOVE_REQ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  pm_qos_read_value (int /*<<< orphan*/ *) ; 
 int pm_qos_update_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int pm_qos_update_target (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apply_constraint(struct dev_pm_qos_request *req,
			    enum pm_qos_req_action action, s32 value)
{
	struct dev_pm_qos *qos = req->dev->power.qos;
	int ret;

	switch(req->type) {
	case DEV_PM_QOS_RESUME_LATENCY:
		if (WARN_ON(action != PM_QOS_REMOVE_REQ && value < 0))
			value = 0;

		ret = pm_qos_update_target(&qos->resume_latency,
					   &req->data.pnode, action, value);
		break;
	case DEV_PM_QOS_LATENCY_TOLERANCE:
		ret = pm_qos_update_target(&qos->latency_tolerance,
					   &req->data.pnode, action, value);
		if (ret) {
			value = pm_qos_read_value(&qos->latency_tolerance);
			req->dev->power.set_latency_tolerance(req->dev, value);
		}
		break;
	case DEV_PM_QOS_FLAGS:
		ret = pm_qos_update_flags(&qos->flags, &req->data.flr,
					  action, value);
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}