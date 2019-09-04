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
struct venus_inst {int /*<<< orphan*/  done; TYPE_1__* core; } ;
struct hfi_ops {int (* session_flush ) (struct venus_inst*,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {struct hfi_ops* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_FLUSH_ALL ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int stub1 (struct venus_inst*,int /*<<< orphan*/ ) ; 
 int wait_session_msg (struct venus_inst*) ; 

int hfi_session_flush(struct venus_inst *inst)
{
	const struct hfi_ops *ops = inst->core->ops;
	int ret;

	reinit_completion(&inst->done);

	ret = ops->session_flush(inst, HFI_FLUSH_ALL);
	if (ret)
		return ret;

	ret = wait_session_msg(inst);
	if (ret)
		return ret;

	return 0;
}