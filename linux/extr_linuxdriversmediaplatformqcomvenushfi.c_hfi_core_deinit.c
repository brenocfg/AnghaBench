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
struct venus_core {scalar_t__ state; int /*<<< orphan*/  lock; TYPE_1__* ops; int /*<<< orphan*/  insts_count; int /*<<< orphan*/  instances; } ;
struct TYPE_2__ {int (* core_deinit ) (struct venus_core*) ;} ;

/* Variables and functions */
 scalar_t__ CORE_UNINIT ; 
 int EBUSY ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct venus_core*) ; 
 int /*<<< orphan*/  wait_var_event (int /*<<< orphan*/ *,int) ; 

int hfi_core_deinit(struct venus_core *core, bool blocking)
{
	int ret = 0, empty;

	mutex_lock(&core->lock);

	if (core->state == CORE_UNINIT)
		goto unlock;

	empty = list_empty(&core->instances);

	if (!empty && !blocking) {
		ret = -EBUSY;
		goto unlock;
	}

	if (!empty) {
		mutex_unlock(&core->lock);
		wait_var_event(&core->insts_count,
			       !atomic_read(&core->insts_count));
		mutex_lock(&core->lock);
	}

	ret = core->ops->core_deinit(core);

	if (!ret)
		core->state = CORE_UNINIT;

unlock:
	mutex_unlock(&core->lock);
	return ret;
}