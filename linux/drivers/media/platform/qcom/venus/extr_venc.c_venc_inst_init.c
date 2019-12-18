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
struct venus_inst {int width; int out_width; int out_height; int fps; int /*<<< orphan*/  hfi_codec; TYPE_1__ timeperframe; int /*<<< orphan*/  height; int /*<<< orphan*/ * fmt_out; int /*<<< orphan*/ * fmt_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int,int) ; 
 int /*<<< orphan*/  HFI_VIDEO_CODEC_H264 ; 
 int /*<<< orphan*/ * venc_formats ; 

__attribute__((used)) static void venc_inst_init(struct venus_inst *inst)
{
	inst->fmt_cap = &venc_formats[2];
	inst->fmt_out = &venc_formats[0];
	inst->width = 1280;
	inst->height = ALIGN(720, 32);
	inst->out_width = 1280;
	inst->out_height = 720;
	inst->fps = 15;
	inst->timeperframe.numerator = 1;
	inst->timeperframe.denominator = 15;
	inst->hfi_codec = HFI_VIDEO_CODEC_H264;
}