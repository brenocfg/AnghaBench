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
struct TYPE_2__ {int /*<<< orphan*/ * handle; } ;
struct qcom_slim_ngd_ctrl {TYPE_1__ qmi; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qmi_handle_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qcom_slim_qmi_exit(struct qcom_slim_ngd_ctrl *ctrl)
{
	if (!ctrl->qmi.handle)
		return;

	qmi_handle_release(ctrl->qmi.handle);
	devm_kfree(ctrl->dev, ctrl->qmi.handle);
	ctrl->qmi.handle = NULL;
}