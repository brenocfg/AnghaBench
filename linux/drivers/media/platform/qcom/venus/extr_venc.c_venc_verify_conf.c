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
struct venus_inst {scalar_t__ num_input_bufs; scalar_t__ num_output_bufs; TYPE_2__* core; } ;
struct hfi_buffer_requirements {scalar_t__ count_actual; } ;
typedef  enum hfi_version { ____Placeholder_hfi_version } hfi_version ;
struct TYPE_4__ {TYPE_1__* res; } ;
struct TYPE_3__ {int hfi_version; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HFI_BUFFER_INPUT ; 
 int /*<<< orphan*/  HFI_BUFFER_OUTPUT ; 
 scalar_t__ HFI_BUFREQ_COUNT_MIN (struct hfi_buffer_requirements*,int) ; 
 int venus_helper_get_bufreq (struct venus_inst*,int /*<<< orphan*/ ,struct hfi_buffer_requirements*) ; 

__attribute__((used)) static int venc_verify_conf(struct venus_inst *inst)
{
	enum hfi_version ver = inst->core->res->hfi_version;
	struct hfi_buffer_requirements bufreq;
	int ret;

	if (!inst->num_input_bufs || !inst->num_output_bufs)
		return -EINVAL;

	ret = venus_helper_get_bufreq(inst, HFI_BUFFER_OUTPUT, &bufreq);
	if (ret)
		return ret;

	if (inst->num_output_bufs < bufreq.count_actual ||
	    inst->num_output_bufs < HFI_BUFREQ_COUNT_MIN(&bufreq, ver))
		return -EINVAL;

	ret = venus_helper_get_bufreq(inst, HFI_BUFFER_INPUT, &bufreq);
	if (ret)
		return ret;

	if (inst->num_input_bufs < bufreq.count_actual ||
	    inst->num_input_bufs < HFI_BUFREQ_COUNT_MIN(&bufreq, ver))
		return -EINVAL;

	return 0;
}