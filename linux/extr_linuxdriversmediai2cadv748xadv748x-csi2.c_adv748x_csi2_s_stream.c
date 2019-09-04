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
struct v4l2_subdev {int dummy; } ;
struct adv748x_csi2 {int /*<<< orphan*/ * pads; } ;

/* Variables and functions */
 size_t ADV748X_CSI2_SINK ; 
 int EPIPE ; 
 struct v4l2_subdev* adv748x_get_remote_sd (int /*<<< orphan*/ *) ; 
 struct adv748x_csi2* adv748x_sd_to_csi2 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  s_stream ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int adv748x_csi2_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct adv748x_csi2 *tx = adv748x_sd_to_csi2(sd);
	struct v4l2_subdev *src;

	src = adv748x_get_remote_sd(&tx->pads[ADV748X_CSI2_SINK]);
	if (!src)
		return -EPIPE;

	return v4l2_subdev_call(src, video, s_stream, enable);
}