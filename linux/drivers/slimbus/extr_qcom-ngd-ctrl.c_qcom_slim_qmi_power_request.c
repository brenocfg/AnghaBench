#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct slimbus_power_req_msg_v01 {scalar_t__ resp_type_valid; int /*<<< orphan*/  pm_req; } ;
struct qcom_slim_ngd_ctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIMBUS_PM_ACTIVE_V01 ; 
 int /*<<< orphan*/  SLIMBUS_PM_INACTIVE_V01 ; 
 int qcom_slim_qmi_send_power_request (struct qcom_slim_ngd_ctrl*,struct slimbus_power_req_msg_v01*) ; 

__attribute__((used)) static int qcom_slim_qmi_power_request(struct qcom_slim_ngd_ctrl *ctrl,
				       bool active)
{
	struct slimbus_power_req_msg_v01 req;

	if (active)
		req.pm_req = SLIMBUS_PM_ACTIVE_V01;
	else
		req.pm_req = SLIMBUS_PM_INACTIVE_V01;

	req.resp_type_valid = 0;

	return qcom_slim_qmi_send_power_request(ctrl, &req);
}