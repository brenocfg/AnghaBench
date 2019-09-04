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
struct venus_inst {scalar_t__ session_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HFI_BUFFER_INPUT ; 
 int /*<<< orphan*/  HFI_BUFFER_OUTPUT ; 
 scalar_t__ VIDC_SESSION_TYPE_DEC ; 
 scalar_t__ VIDC_SESSION_TYPE_ENC ; 
 int /*<<< orphan*/  to_hfi_raw_fmt (int /*<<< orphan*/ ) ; 
 int venus_helper_set_raw_format (struct venus_inst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int venus_helper_set_color_format(struct venus_inst *inst, u32 pixfmt)
{
	u32 hfi_format, buftype;

	if (inst->session_type == VIDC_SESSION_TYPE_DEC)
		buftype = HFI_BUFFER_OUTPUT;
	else if (inst->session_type == VIDC_SESSION_TYPE_ENC)
		buftype = HFI_BUFFER_INPUT;
	else
		return -EINVAL;

	hfi_format = to_hfi_raw_fmt(pixfmt);
	if (!hfi_format)
		return -EINVAL;

	return venus_helper_set_raw_format(inst, hfi_format, buftype);
}