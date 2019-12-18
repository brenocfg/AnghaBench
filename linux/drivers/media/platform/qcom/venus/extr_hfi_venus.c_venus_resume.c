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
struct venus_hfi_device {int suspended; int /*<<< orphan*/  lock; } ;
struct venus_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct venus_hfi_device* to_hfi_priv (struct venus_core*) ; 
 int venus_power_on (struct venus_hfi_device*) ; 

__attribute__((used)) static int venus_resume(struct venus_core *core)
{
	struct venus_hfi_device *hdev = to_hfi_priv(core);
	int ret = 0;

	mutex_lock(&hdev->lock);

	if (!hdev->suspended)
		goto unlock;

	ret = venus_power_on(hdev);

unlock:
	if (!ret)
		hdev->suspended = false;

	mutex_unlock(&hdev->lock);

	return ret;
}