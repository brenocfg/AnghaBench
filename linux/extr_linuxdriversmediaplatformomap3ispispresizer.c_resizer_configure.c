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
struct v4l2_mbus_framefmt {int width; int /*<<< orphan*/  height; int /*<<< orphan*/  code; } ;
struct resizer_luma_yenh {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct isp_res_device {scalar_t__ input; struct v4l2_mbus_framefmt* formats; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  DEFAULT_PHASE ; 
 scalar_t__ RESIZER_INPUT_VP ; 
 size_t RESZ_PAD_SINK ; 
 size_t RESZ_PAD_SOURCE ; 
 int /*<<< orphan*/  RSZ_YUV422 ; 
 int /*<<< orphan*/  resizer_set_crop_params (struct isp_res_device*,struct v4l2_mbus_framefmt*,struct v4l2_mbus_framefmt*) ; 
 int /*<<< orphan*/  resizer_set_input_offset (struct isp_res_device*,int) ; 
 int /*<<< orphan*/  resizer_set_intype (struct isp_res_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resizer_set_luma (struct isp_res_device*,struct resizer_luma_yenh*) ; 
 int /*<<< orphan*/  resizer_set_output_offset (struct isp_res_device*,int) ; 
 int /*<<< orphan*/  resizer_set_output_size (struct isp_res_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resizer_set_phase (struct isp_res_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resizer_set_source (struct isp_res_device*,scalar_t__) ; 
 int /*<<< orphan*/  resizer_set_ycpos (struct isp_res_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void resizer_configure(struct isp_res_device *res)
{
	struct v4l2_mbus_framefmt *informat, *outformat;
	struct resizer_luma_yenh luma = {0, 0, 0, 0};

	resizer_set_source(res, res->input);

	informat = &res->formats[RESZ_PAD_SINK];
	outformat = &res->formats[RESZ_PAD_SOURCE];

	/* RESZ_PAD_SINK */
	if (res->input == RESIZER_INPUT_VP)
		resizer_set_input_offset(res, 0);
	else
		resizer_set_input_offset(res, ALIGN(informat->width, 0x10) * 2);

	/* YUV422 interleaved, default phase, no luma enhancement */
	resizer_set_intype(res, RSZ_YUV422);
	resizer_set_ycpos(res, informat->code);
	resizer_set_phase(res, DEFAULT_PHASE, DEFAULT_PHASE);
	resizer_set_luma(res, &luma);

	/* RESZ_PAD_SOURCE */
	resizer_set_output_offset(res, ALIGN(outformat->width * 2, 32));
	resizer_set_output_size(res, outformat->width, outformat->height);

	resizer_set_crop_params(res, informat, outformat);
}