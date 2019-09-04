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
typedef  int v4l2_std_id ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_STD_525_60 ; 
 int V4L2_STD_625_50 ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int /*<<< orphan*/ ,int,struct v4l2_subdev*,char*) ; 
 int venc_set_ntsc (struct v4l2_subdev*) ; 
 int venc_set_pal (struct v4l2_subdev*) ; 

__attribute__((used)) static int venc_s_std_output(struct v4l2_subdev *sd, v4l2_std_id norm)
{
	v4l2_dbg(debug, 1, sd, "venc_s_std_output\n");

	if (norm & V4L2_STD_525_60)
		return venc_set_ntsc(sd);
	else if (norm & V4L2_STD_625_50)
		return venc_set_pal(sd);

	return -EINVAL;
}