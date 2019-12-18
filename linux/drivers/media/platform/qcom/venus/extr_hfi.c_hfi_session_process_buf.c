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
struct venus_inst {TYPE_1__* core; } ;
struct hfi_ops {int (* session_etb ) (struct venus_inst*,struct hfi_frame_data*) ;int (* session_ftb ) (struct venus_inst*,struct hfi_frame_data*) ;} ;
struct hfi_frame_data {scalar_t__ buffer_type; } ;
struct TYPE_2__ {struct hfi_ops* ops; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HFI_BUFFER_INPUT ; 
 scalar_t__ HFI_BUFFER_OUTPUT ; 
 scalar_t__ HFI_BUFFER_OUTPUT2 ; 
 int stub1 (struct venus_inst*,struct hfi_frame_data*) ; 
 int stub2 (struct venus_inst*,struct hfi_frame_data*) ; 

int hfi_session_process_buf(struct venus_inst *inst, struct hfi_frame_data *fd)
{
	const struct hfi_ops *ops = inst->core->ops;

	if (fd->buffer_type == HFI_BUFFER_INPUT)
		return ops->session_etb(inst, fd);
	else if (fd->buffer_type == HFI_BUFFER_OUTPUT ||
		 fd->buffer_type == HFI_BUFFER_OUTPUT2)
		return ops->session_ftb(inst, fd);

	return -EINVAL;
}