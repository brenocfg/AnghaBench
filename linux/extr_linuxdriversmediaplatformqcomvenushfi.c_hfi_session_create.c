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
struct venus_inst {int /*<<< orphan*/  list; struct hfi_inst_ops const* ops; int /*<<< orphan*/  done; int /*<<< orphan*/  state; struct venus_core* core; } ;
struct venus_core {int /*<<< orphan*/  lock; int /*<<< orphan*/  insts_count; int /*<<< orphan*/  instances; } ;
struct hfi_inst_ops {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INST_UNINIT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int hfi_session_create(struct venus_inst *inst, const struct hfi_inst_ops *ops)
{
	struct venus_core *core = inst->core;

	if (!ops)
		return -EINVAL;

	inst->state = INST_UNINIT;
	init_completion(&inst->done);
	inst->ops = ops;

	mutex_lock(&core->lock);
	list_add_tail(&inst->list, &core->instances);
	atomic_inc(&core->insts_count);
	mutex_unlock(&core->lock);

	return 0;
}