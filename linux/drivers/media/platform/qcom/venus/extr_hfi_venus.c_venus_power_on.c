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
struct venus_hfi_device {int power_enabled; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int venus_run (struct venus_hfi_device*) ; 
 int venus_set_hw_state_resume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  venus_set_hw_state_suspend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int venus_power_on(struct venus_hfi_device *hdev)
{
	int ret;

	if (hdev->power_enabled)
		return 0;

	ret = venus_set_hw_state_resume(hdev->core);
	if (ret)
		goto err;

	ret = venus_run(hdev);
	if (ret)
		goto err_suspend;

	hdev->power_enabled = true;

	return 0;

err_suspend:
	venus_set_hw_state_suspend(hdev->core);
err:
	hdev->power_enabled = false;
	return ret;
}