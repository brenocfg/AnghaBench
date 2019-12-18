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
typedef  void* u32 ;
struct venus_inst {int dummy; } ;
struct hfi_buffer_size_actual {void* size; void* type; } ;

/* Variables and functions */
 void* HFI_PROPERTY_PARAM_BUFFER_SIZE_ACTUAL ; 
 int hfi_session_set_property (struct venus_inst*,void* const,struct hfi_buffer_size_actual*) ; 

int venus_helper_set_bufsize(struct venus_inst *inst, u32 bufsize, u32 buftype)
{
	const u32 ptype = HFI_PROPERTY_PARAM_BUFFER_SIZE_ACTUAL;
	struct hfi_buffer_size_actual bufsz;

	bufsz.type = buftype;
	bufsz.size = bufsize;

	return hfi_session_set_property(inst, ptype, &bufsz);
}