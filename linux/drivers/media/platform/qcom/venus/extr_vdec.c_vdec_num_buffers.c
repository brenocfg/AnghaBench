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
struct venus_inst {TYPE_2__* core; } ;
struct hfi_buffer_requirements {int dummy; } ;
typedef  enum hfi_version { ____Placeholder_hfi_version } hfi_version ;
struct TYPE_4__ {TYPE_1__* res; } ;
struct TYPE_3__ {int hfi_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_BUFFER_INPUT ; 
 int /*<<< orphan*/  HFI_BUFFER_OUTPUT ; 
 unsigned int HFI_BUFREQ_COUNT_MIN (struct hfi_buffer_requirements*,int) ; 
 int venus_helper_get_bufreq (struct venus_inst*,int /*<<< orphan*/ ,struct hfi_buffer_requirements*) ; 

__attribute__((used)) static int vdec_num_buffers(struct venus_inst *inst, unsigned int *in_num,
			    unsigned int *out_num)
{
	enum hfi_version ver = inst->core->res->hfi_version;
	struct hfi_buffer_requirements bufreq;
	int ret;

	*in_num = *out_num = 0;

	ret = venus_helper_get_bufreq(inst, HFI_BUFFER_INPUT, &bufreq);
	if (ret)
		return ret;

	*in_num = HFI_BUFREQ_COUNT_MIN(&bufreq, ver);

	ret = venus_helper_get_bufreq(inst, HFI_BUFFER_OUTPUT, &bufreq);
	if (ret)
		return ret;

	*out_num = HFI_BUFREQ_COUNT_MIN(&bufreq, ver);

	return 0;
}