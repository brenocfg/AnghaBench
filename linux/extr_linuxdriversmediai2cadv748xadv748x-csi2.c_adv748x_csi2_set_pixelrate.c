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
struct adv748x_csi2 {int /*<<< orphan*/  pixel_rate; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int EINVAL ; 
 struct adv748x_csi2* adv748x_sd_to_csi2 (struct v4l2_subdev*) ; 
 int v4l2_ctrl_s_ctrl_int64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int adv748x_csi2_set_pixelrate(struct v4l2_subdev *sd, s64 rate)
{
	struct adv748x_csi2 *tx = adv748x_sd_to_csi2(sd);

	if (!tx->pixel_rate)
		return -EINVAL;

	return v4l2_ctrl_s_ctrl_int64(tx->pixel_rate, rate);
}