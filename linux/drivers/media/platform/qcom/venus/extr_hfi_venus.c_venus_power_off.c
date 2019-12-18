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
 int venus_halt_axi (struct venus_hfi_device*) ; 
 int venus_set_hw_state_suspend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int venus_power_off(struct venus_hfi_device *hdev)
{
	int ret;

	if (!hdev->power_enabled)
		return 0;

	ret = venus_set_hw_state_suspend(hdev->core);
	if (ret)
		return ret;

	ret = venus_halt_axi(hdev);
	if (ret)
		return ret;

	hdev->power_enabled = false;

	return 0;
}