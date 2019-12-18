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
struct sockaddr_qrtr {int dummy; } ;
struct TYPE_2__ {scalar_t__ result; } ;
struct slimbus_power_resp_msg_v01 {TYPE_1__ resp; } ;
struct qmi_txn {int /*<<< orphan*/  completion; } ;
struct qmi_handle {int dummy; } ;

/* Variables and functions */
 scalar_t__ QMI_RESULT_SUCCESS_V01 ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 

__attribute__((used)) static void qcom_slim_qmi_power_resp_cb(struct qmi_handle *handle,
					struct sockaddr_qrtr *sq,
					struct qmi_txn *txn, const void *data)
{
	struct slimbus_power_resp_msg_v01 *resp;

	resp = (struct slimbus_power_resp_msg_v01 *)data;
	if (resp->resp.result != QMI_RESULT_SUCCESS_V01)
		pr_err("QMI power request failed 0x%x\n",
				resp->resp.result);

	complete(&txn->completion);
}