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
typedef  union hfi_get_property {int dummy; } hfi_get_property ;
typedef  int /*<<< orphan*/  u32 ;
struct venus_inst {scalar_t__ state; union hfi_get_property hprop; int /*<<< orphan*/  done; TYPE_1__* core; } ;
struct hfi_ops {int (* session_get_property ) (struct venus_inst*,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {struct hfi_ops* ops; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ INST_INIT ; 
 scalar_t__ INST_STOP ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int stub1 (struct venus_inst*,int /*<<< orphan*/ ) ; 
 int wait_session_msg (struct venus_inst*) ; 

int hfi_session_get_property(struct venus_inst *inst, u32 ptype,
			     union hfi_get_property *hprop)
{
	const struct hfi_ops *ops = inst->core->ops;
	int ret;

	if (inst->state < INST_INIT || inst->state >= INST_STOP)
		return -EINVAL;

	reinit_completion(&inst->done);

	ret = ops->session_get_property(inst, ptype);
	if (ret)
		return ret;

	ret = wait_session_msg(inst);
	if (ret)
		return ret;

	*hprop = inst->hprop;

	return 0;
}