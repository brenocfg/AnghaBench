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
struct venus_inst {int dummy; } ;
struct hfi_buffer_requirements {unsigned int count_actual; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_BUFFER_INPUT ; 
 int /*<<< orphan*/  hfi_session_deinit (struct venus_inst*) ; 
 int venc_init_session (struct venus_inst*) ; 
 int venus_helper_get_bufreq (struct venus_inst*,int /*<<< orphan*/ ,struct hfi_buffer_requirements*) ; 

__attribute__((used)) static int venc_out_num_buffers(struct venus_inst *inst, unsigned int *num)
{
	struct hfi_buffer_requirements bufreq;
	int ret;

	ret = venc_init_session(inst);
	if (ret)
		return ret;

	ret = venus_helper_get_bufreq(inst, HFI_BUFFER_INPUT, &bufreq);

	*num = bufreq.count_actual;

	hfi_session_deinit(inst);

	return ret;
}