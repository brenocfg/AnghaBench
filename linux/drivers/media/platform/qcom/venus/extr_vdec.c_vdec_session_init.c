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
struct venus_inst {TYPE_1__* fmt_out; } ;
struct TYPE_2__ {int /*<<< orphan*/  pixfmt; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  frame_height_min (struct venus_inst*) ; 
 int /*<<< orphan*/  frame_width_min (struct venus_inst*) ; 
 int /*<<< orphan*/  hfi_session_deinit (struct venus_inst*) ; 
 int hfi_session_init (struct venus_inst*,int /*<<< orphan*/ ) ; 
 int venus_helper_set_input_resolution (struct venus_inst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vdec_session_init(struct venus_inst *inst)
{
	int ret;

	ret = hfi_session_init(inst, inst->fmt_out->pixfmt);
	if (ret == -EINVAL)
		return 0;
	else if (ret)
		return ret;

	ret = venus_helper_set_input_resolution(inst, frame_width_min(inst),
						frame_height_min(inst));
	if (ret)
		goto deinit;

	return 0;
deinit:
	hfi_session_deinit(inst);
	return ret;
}