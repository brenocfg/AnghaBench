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
struct venc_state {int /*<<< orphan*/  std; scalar_t__ output; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_STD_525_60 ; 
 struct venc_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*) ; 
 int venc_s_routing (struct v4l2_subdev*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int venc_s_std_output (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int venc_initialize(struct v4l2_subdev *sd)
{
	struct venc_state *venc = to_state(sd);
	int ret;

	/* Set default to output to composite and std to NTSC */
	venc->output = 0;
	venc->std = V4L2_STD_525_60;

	ret = venc_s_routing(sd, 0, venc->output, 0);
	if (ret < 0) {
		v4l2_err(sd, "Error setting output during init\n");
		return -EINVAL;
	}

	ret = venc_s_std_output(sd, venc->std);
	if (ret < 0) {
		v4l2_err(sd, "Error setting std during init\n");
		return -EINVAL;
	}

	return ret;
}