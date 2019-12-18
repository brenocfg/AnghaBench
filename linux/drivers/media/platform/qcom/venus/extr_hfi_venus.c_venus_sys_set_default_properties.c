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
struct venus_hfi_device {TYPE_1__* core; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 scalar_t__ IS_V4 (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int /*<<< orphan*/  venus_fw_debug ; 
 int /*<<< orphan*/  venus_fw_low_power_mode ; 
 int venus_sys_idle_indicator ; 
 int venus_sys_set_debug (struct venus_hfi_device*,int /*<<< orphan*/ ) ; 
 int venus_sys_set_idle_message (struct venus_hfi_device*,int) ; 
 int venus_sys_set_power_control (struct venus_hfi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int venus_sys_set_default_properties(struct venus_hfi_device *hdev)
{
	struct device *dev = hdev->core->dev;
	int ret;

	ret = venus_sys_set_debug(hdev, venus_fw_debug);
	if (ret)
		dev_warn(dev, "setting fw debug msg ON failed (%d)\n", ret);

	/*
	 * Idle indicator is disabled by default on some 4xx firmware versions,
	 * enable it explicitly in order to make suspend functional by checking
	 * WFI (wait-for-interrupt) bit.
	 */
	if (IS_V4(hdev->core))
		venus_sys_idle_indicator = true;

	ret = venus_sys_set_idle_message(hdev, venus_sys_idle_indicator);
	if (ret)
		dev_warn(dev, "setting idle response ON failed (%d)\n", ret);

	ret = venus_sys_set_power_control(hdev, venus_fw_low_power_mode);
	if (ret)
		dev_warn(dev, "setting hw power collapse ON failed (%d)\n",
			 ret);

	return ret;
}