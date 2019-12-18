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
struct venus_hfi_device {int suspended; int /*<<< orphan*/  lock; int /*<<< orphan*/  power_enabled; } ;
struct venus_core {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int readx_poll_timeout (int /*<<< orphan*/ ,struct venus_hfi_device*,int,int,int,int) ; 
 struct venus_hfi_device* to_hfi_priv (struct venus_core*) ; 
 int /*<<< orphan*/  venus_cpu_and_video_core_idle ; 
 int /*<<< orphan*/  venus_cpu_idle_and_pc_ready ; 
 int venus_is_valid_state (struct venus_hfi_device*) ; 
 int venus_power_off (struct venus_hfi_device*) ; 
 int venus_prepare_power_collapse (struct venus_hfi_device*,int) ; 

__attribute__((used)) static int venus_suspend_3xx(struct venus_core *core)
{
	struct venus_hfi_device *hdev = to_hfi_priv(core);
	struct device *dev = core->dev;
	bool val;
	int ret;

	if (!hdev->power_enabled || hdev->suspended)
		return 0;

	mutex_lock(&hdev->lock);
	ret = venus_is_valid_state(hdev);
	mutex_unlock(&hdev->lock);

	if (!ret) {
		dev_err(dev, "bad state, cannot suspend\n");
		return -EINVAL;
	}

	/*
	 * Power collapse sequence for Venus 3xx and 4xx versions:
	 * 1. Check for ARM9 and video core to be idle by checking WFI bit
	 *    (bit 0) in CPU status register and by checking Idle (bit 30) in
	 *    Control status register for video core.
	 * 2. Send a command to prepare for power collapse.
	 * 3. Check for WFI and PC_READY bits.
	 */
	ret = readx_poll_timeout(venus_cpu_and_video_core_idle, hdev, val, val,
				 1500, 100 * 1500);
	if (ret)
		return ret;

	ret = venus_prepare_power_collapse(hdev, false);
	if (ret) {
		dev_err(dev, "prepare for power collapse fail (%d)\n", ret);
		return ret;
	}

	ret = readx_poll_timeout(venus_cpu_idle_and_pc_ready, hdev, val, val,
				 1500, 100 * 1500);
	if (ret)
		return ret;

	mutex_lock(&hdev->lock);

	ret = venus_power_off(hdev);
	if (ret) {
		dev_err(dev, "venus_power_off (%d)\n", ret);
		mutex_unlock(&hdev->lock);
		return ret;
	}

	hdev->suspended = true;

	mutex_unlock(&hdev->lock);

	return 0;
}