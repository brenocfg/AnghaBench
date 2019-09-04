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
struct venus_hfi_device {int power_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  TZBSP_VIDEO_STATE_RESUME ; 
 int /*<<< orphan*/  TZBSP_VIDEO_STATE_SUSPEND ; 
 int qcom_scm_set_remote_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int venus_run (struct venus_hfi_device*) ; 

__attribute__((used)) static int venus_power_on(struct venus_hfi_device *hdev)
{
	int ret;

	if (hdev->power_enabled)
		return 0;

	ret = qcom_scm_set_remote_state(TZBSP_VIDEO_STATE_RESUME, 0);
	if (ret)
		goto err;

	ret = venus_run(hdev);
	if (ret)
		goto err_suspend;

	hdev->power_enabled = true;

	return 0;

err_suspend:
	qcom_scm_set_remote_state(TZBSP_VIDEO_STATE_SUSPEND, 0);
err:
	hdev->power_enabled = false;
	return ret;
}