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
typedef  int /*<<< orphan*/  u32 ;
struct venus_inst {scalar_t__ state; int /*<<< orphan*/  hfi_codec; int /*<<< orphan*/  session_type; int /*<<< orphan*/  done; struct venus_core* core; } ;
struct venus_core {struct hfi_ops* ops; } ;
struct hfi_ops {int (* session_init ) (struct venus_inst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ INST_INIT ; 
 scalar_t__ INST_UNINIT ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int stub1 (struct venus_inst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_codec_type (int /*<<< orphan*/ ) ; 
 int wait_session_msg (struct venus_inst*) ; 

int hfi_session_init(struct venus_inst *inst, u32 pixfmt)
{
	struct venus_core *core = inst->core;
	const struct hfi_ops *ops = core->ops;
	int ret;

	if (inst->state != INST_UNINIT)
		return -EINVAL;

	inst->hfi_codec = to_codec_type(pixfmt);
	reinit_completion(&inst->done);

	ret = ops->session_init(inst, inst->session_type, inst->hfi_codec);
	if (ret)
		return ret;

	ret = wait_session_msg(inst);
	if (ret)
		return ret;

	inst->state = INST_INIT;

	return 0;
}