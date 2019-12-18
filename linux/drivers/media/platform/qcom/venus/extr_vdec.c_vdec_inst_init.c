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
struct TYPE_2__ {int numerator; int denominator; } ;
struct venus_inst {int fps; int /*<<< orphan*/  opb_buftype; TYPE_1__ timeperframe; int /*<<< orphan*/  out_height; void* out_width; int /*<<< orphan*/  height; void* width; int /*<<< orphan*/ * fmt_cap; int /*<<< orphan*/ * fmt_out; int /*<<< orphan*/  hfi_codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HFI_BUFFER_OUTPUT ; 
 int /*<<< orphan*/  HFI_VIDEO_CODEC_H264 ; 
 int /*<<< orphan*/  frame_height_min (struct venus_inst*) ; 
 void* frame_width_min (struct venus_inst*) ; 
 int /*<<< orphan*/ * vdec_formats ; 

__attribute__((used)) static void vdec_inst_init(struct venus_inst *inst)
{
	inst->hfi_codec = HFI_VIDEO_CODEC_H264;
	inst->fmt_out = &vdec_formats[6];
	inst->fmt_cap = &vdec_formats[0];
	inst->width = frame_width_min(inst);
	inst->height = ALIGN(frame_height_min(inst), 32);
	inst->out_width = frame_width_min(inst);
	inst->out_height = frame_height_min(inst);
	inst->fps = 30;
	inst->timeperframe.numerator = 1;
	inst->timeperframe.denominator = 30;
	inst->opb_buftype = HFI_BUFFER_OUTPUT;
}