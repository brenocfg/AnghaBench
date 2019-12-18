#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tb_switch {int /*<<< orphan*/  dev; TYPE_2__* tb; TYPE_1__* nvm; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int authenticating; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int kstrtobool (char const*,int*) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvm_authenticate_complete (struct tb_switch*) ; 
 int nvm_authenticate_device (struct tb_switch*) ; 
 int nvm_authenticate_host (struct tb_switch*) ; 
 int /*<<< orphan*/  nvm_authenticate_start (struct tb_switch*) ; 
 int /*<<< orphan*/  nvm_clear_auth_status (struct tb_switch*) ; 
 int nvm_validate_and_write (struct tb_switch*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 
 int restart_syscall () ; 
 int /*<<< orphan*/  tb_route (struct tb_switch*) ; 
 struct tb_switch* tb_to_switch (struct device*) ; 

__attribute__((used)) static ssize_t nvm_authenticate_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct tb_switch *sw = tb_to_switch(dev);
	bool val;
	int ret;

	pm_runtime_get_sync(&sw->dev);

	if (!mutex_trylock(&sw->tb->lock)) {
		ret = restart_syscall();
		goto exit_rpm;
	}

	/* If NVMem devices are not yet added */
	if (!sw->nvm) {
		ret = -EAGAIN;
		goto exit_unlock;
	}

	ret = kstrtobool(buf, &val);
	if (ret)
		goto exit_unlock;

	/* Always clear the authentication status */
	nvm_clear_auth_status(sw);

	if (val) {
		if (!sw->nvm->buf) {
			ret = -EINVAL;
			goto exit_unlock;
		}

		ret = nvm_validate_and_write(sw);
		if (ret)
			goto exit_unlock;

		sw->nvm->authenticating = true;

		if (!tb_route(sw)) {
			/*
			 * Keep root port from suspending as long as the
			 * NVM upgrade process is running.
			 */
			nvm_authenticate_start(sw);
			ret = nvm_authenticate_host(sw);
			if (ret)
				nvm_authenticate_complete(sw);
		} else {
			ret = nvm_authenticate_device(sw);
		}
	}

exit_unlock:
	mutex_unlock(&sw->tb->lock);
exit_rpm:
	pm_runtime_mark_last_busy(&sw->dev);
	pm_runtime_put_autosuspend(&sw->dev);

	if (ret)
		return ret;
	return count;
}