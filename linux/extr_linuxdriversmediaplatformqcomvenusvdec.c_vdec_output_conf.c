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
typedef  int u32 ;
struct venus_inst {int out_width; int out_height; int opb_fmt; int dpb_fmt; void* output_buf_size; void* output2_buf_size; void* dpb_buftype; void* opb_buftype; TYPE_2__* fmt_cap; struct venus_core* core; } ;
struct venus_core {TYPE_1__* res; } ;
struct hfi_enable {int enable; } ;
struct TYPE_4__ {int /*<<< orphan*/  pixfmt; } ;
struct TYPE_3__ {scalar_t__ hfi_version; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 void* HFI_BUFFER_OUTPUT ; 
 void* HFI_BUFFER_OUTPUT2 ; 
 int HFI_PROPERTY_PARAM_VDEC_CONTINUE_DATA_TRANSFER ; 
 scalar_t__ HFI_VERSION_1XX ; 
 scalar_t__ IS_V3 (struct venus_core*) ; 
 scalar_t__ IS_V4 (struct venus_core*) ; 
 int /*<<< orphan*/  VIDC_CORE_ID_1 ; 
 int /*<<< orphan*/  VIDC_WORK_MODE_2 ; 
 int hfi_session_set_property (struct venus_inst*,int,struct hfi_enable*) ; 
 scalar_t__ is_ubwc_fmt (int) ; 
 void* venus_helper_get_framesz_raw (int,int,int) ; 
 int venus_helper_get_out_fmts (struct venus_inst*,int /*<<< orphan*/ ,int*,int*,int) ; 
 int venus_helper_set_bufsize (struct venus_inst*,void*,void*) ; 
 int venus_helper_set_core_usage (struct venus_inst*,int /*<<< orphan*/ ) ; 
 int venus_helper_set_dyn_bufmode (struct venus_inst*) ; 
 int venus_helper_set_multistream (struct venus_inst*,int,int) ; 
 int venus_helper_set_output_resolution (struct venus_inst*,int,int,void*) ; 
 int venus_helper_set_raw_format (struct venus_inst*,int,void*) ; 
 int venus_helper_set_work_mode (struct venus_inst*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vdec_output_conf(struct venus_inst *inst)
{
	struct venus_core *core = inst->core;
	struct hfi_enable en = { .enable = 1 };
	u32 width = inst->out_width;
	u32 height = inst->out_height;
	u32 out_fmt, out2_fmt;
	bool ubwc = false;
	u32 ptype;
	int ret;

	ret = venus_helper_set_work_mode(inst, VIDC_WORK_MODE_2);
	if (ret)
		return ret;

	ret = venus_helper_set_core_usage(inst, VIDC_CORE_ID_1);
	if (ret)
		return ret;

	if (core->res->hfi_version == HFI_VERSION_1XX) {
		ptype = HFI_PROPERTY_PARAM_VDEC_CONTINUE_DATA_TRANSFER;
		ret = hfi_session_set_property(inst, ptype, &en);
		if (ret)
			return ret;
	}

	/* Force searching UBWC formats for bigger then HD resolutions */
	if (width > 1920 && height > ALIGN(1080, 32))
		ubwc = true;

	/* For Venus v4 UBWC format is mandatory */
	if (IS_V4(core))
		ubwc = true;

	ret = venus_helper_get_out_fmts(inst, inst->fmt_cap->pixfmt, &out_fmt,
					&out2_fmt, ubwc);
	if (ret)
		return ret;

	inst->output_buf_size =
			venus_helper_get_framesz_raw(out_fmt, width, height);
	inst->output2_buf_size =
			venus_helper_get_framesz_raw(out2_fmt, width, height);

	if (is_ubwc_fmt(out_fmt)) {
		inst->opb_buftype = HFI_BUFFER_OUTPUT2;
		inst->opb_fmt = out2_fmt;
		inst->dpb_buftype = HFI_BUFFER_OUTPUT;
		inst->dpb_fmt = out_fmt;
	} else if (is_ubwc_fmt(out2_fmt)) {
		inst->opb_buftype = HFI_BUFFER_OUTPUT;
		inst->opb_fmt = out_fmt;
		inst->dpb_buftype = HFI_BUFFER_OUTPUT2;
		inst->dpb_fmt = out2_fmt;
	} else {
		inst->opb_buftype = HFI_BUFFER_OUTPUT;
		inst->opb_fmt = out_fmt;
		inst->dpb_buftype = 0;
		inst->dpb_fmt = 0;
	}

	ret = venus_helper_set_raw_format(inst, inst->opb_fmt,
					  inst->opb_buftype);
	if (ret)
		return ret;

	if (inst->dpb_fmt) {
		ret = venus_helper_set_multistream(inst, false, true);
		if (ret)
			return ret;

		ret = venus_helper_set_raw_format(inst, inst->dpb_fmt,
						  inst->dpb_buftype);
		if (ret)
			return ret;

		ret = venus_helper_set_output_resolution(inst, width, height,
							 HFI_BUFFER_OUTPUT2);
		if (ret)
			return ret;
	}

	if (IS_V3(core) || IS_V4(core)) {
		if (inst->output2_buf_size) {
			ret = venus_helper_set_bufsize(inst,
						       inst->output2_buf_size,
						       HFI_BUFFER_OUTPUT2);
			if (ret)
				return ret;
		}

		if (inst->output_buf_size) {
			ret = venus_helper_set_bufsize(inst,
						       inst->output_buf_size,
						       HFI_BUFFER_OUTPUT);
			if (ret)
				return ret;
		}
	}

	ret = venus_helper_set_dyn_bufmode(inst);
	if (ret)
		return ret;

	return 0;
}