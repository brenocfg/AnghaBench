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
struct venus_core {scalar_t__ state; scalar_t__ error; int /*<<< orphan*/  lock; int /*<<< orphan*/  done; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* core_init ) (struct venus_core*) ;} ;

/* Variables and functions */
 scalar_t__ CORE_INIT ; 
 int EIO ; 
 int ETIMEDOUT ; 
 scalar_t__ HFI_ERR_NONE ; 
 int /*<<< orphan*/  TIMEOUT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int stub1 (struct venus_core*) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int hfi_core_init(struct venus_core *core)
{
	int ret = 0;

	mutex_lock(&core->lock);

	if (core->state >= CORE_INIT)
		goto unlock;

	reinit_completion(&core->done);

	ret = core->ops->core_init(core);
	if (ret)
		goto unlock;

	ret = wait_for_completion_timeout(&core->done, TIMEOUT);
	if (!ret) {
		ret = -ETIMEDOUT;
		goto unlock;
	}

	ret = 0;

	if (core->error != HFI_ERR_NONE) {
		ret = -EIO;
		goto unlock;
	}

	core->state = CORE_INIT;
unlock:
	mutex_unlock(&core->lock);
	return ret;
}