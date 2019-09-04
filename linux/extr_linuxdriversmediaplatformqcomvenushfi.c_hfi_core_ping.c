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
struct venus_core {scalar_t__ error; int /*<<< orphan*/  lock; int /*<<< orphan*/  done; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* core_ping ) (struct venus_core*,int) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int ETIMEDOUT ; 
 scalar_t__ HFI_ERR_NONE ; 
 int /*<<< orphan*/  TIMEOUT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct venus_core*,int) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int hfi_core_ping(struct venus_core *core)
{
	int ret;

	mutex_lock(&core->lock);

	ret = core->ops->core_ping(core, 0xbeef);
	if (ret)
		goto unlock;

	ret = wait_for_completion_timeout(&core->done, TIMEOUT);
	if (!ret) {
		ret = -ETIMEDOUT;
		goto unlock;
	}
	ret = 0;
	if (core->error != HFI_ERR_NONE)
		ret = -ENODEV;
unlock:
	mutex_unlock(&core->lock);
	return ret;
}