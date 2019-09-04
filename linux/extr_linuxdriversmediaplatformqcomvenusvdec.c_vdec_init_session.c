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
struct venus_inst {TYPE_2__* fmt_cap; int /*<<< orphan*/  out_height; int /*<<< orphan*/  out_width; TYPE_1__* fmt_out; } ;
struct TYPE_4__ {int /*<<< orphan*/  pixfmt; } ;
struct TYPE_3__ {int /*<<< orphan*/  pixfmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  hfi_session_deinit (struct venus_inst*) ; 
 int hfi_session_init (struct venus_inst*,int /*<<< orphan*/ ) ; 
 int venus_helper_set_color_format (struct venus_inst*,int /*<<< orphan*/ ) ; 
 int venus_helper_set_input_resolution (struct venus_inst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vdec_init_session(struct venus_inst *inst)
{
	int ret;

	ret = hfi_session_init(inst, inst->fmt_out->pixfmt);
	if (ret)
		return ret;

	ret = venus_helper_set_input_resolution(inst, inst->out_width,
						inst->out_height);
	if (ret)
		goto deinit;

	ret = venus_helper_set_color_format(inst, inst->fmt_cap->pixfmt);
	if (ret)
		goto deinit;

	return 0;
deinit:
	hfi_session_deinit(inst);
	return ret;
}