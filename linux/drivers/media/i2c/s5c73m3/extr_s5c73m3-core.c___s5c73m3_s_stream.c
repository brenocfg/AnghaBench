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
typedef  int u16 ;
struct v4l2_subdev {int dummy; } ;
struct s5c73m3 {scalar_t__ mbus_code; int streaming; scalar_t__ apply_fiv; scalar_t__ apply_fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMM_IMG_OUTPUT ; 
 int COMM_IMG_OUTPUT_INTERLEAVED ; 
 int COMM_IMG_OUTPUT_YUV ; 
 int /*<<< orphan*/  COMM_SENSOR_STREAMING ; 
 int /*<<< orphan*/  REG_STATUS_ISP_COMMAND_COMPLETED ; 
 scalar_t__ S5C73M3_JPEG_FMT ; 
 int s5c73m3_check_status (struct s5c73m3*,int /*<<< orphan*/ ) ; 
 int s5c73m3_isp_command (struct s5c73m3*,int /*<<< orphan*/ ,int) ; 
 int s5c73m3_set_frame_rate (struct s5c73m3*) ; 
 int s5c73m3_set_frame_size (struct s5c73m3*) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*,int) ; 

__attribute__((used)) static int __s5c73m3_s_stream(struct s5c73m3 *state, struct v4l2_subdev *sd,
								int on)
{
	u16 mode;
	int ret;

	if (on && state->apply_fmt) {
		if (state->mbus_code == S5C73M3_JPEG_FMT)
			mode = COMM_IMG_OUTPUT_INTERLEAVED;
		else
			mode = COMM_IMG_OUTPUT_YUV;

		ret = s5c73m3_isp_command(state, COMM_IMG_OUTPUT, mode);
		if (!ret)
			ret = s5c73m3_set_frame_size(state);
		if (ret)
			return ret;
		state->apply_fmt = 0;
	}

	ret = s5c73m3_isp_command(state, COMM_SENSOR_STREAMING, !!on);
	if (ret)
		return ret;

	state->streaming = !!on;

	if (!on)
		return ret;

	if (state->apply_fiv) {
		ret = s5c73m3_set_frame_rate(state);
		if (ret < 0)
			v4l2_err(sd, "Error setting frame rate(%d)\n", ret);
	}

	return s5c73m3_check_status(state, REG_STATUS_ISP_COMMAND_COMPLETED);
}