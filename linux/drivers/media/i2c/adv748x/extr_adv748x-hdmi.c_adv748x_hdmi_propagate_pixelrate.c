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
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pixelclock; } ;
struct v4l2_dv_timings {TYPE_1__ bt; } ;
struct adv748x_hdmi {int /*<<< orphan*/  sd; int /*<<< orphan*/ * pads; } ;

/* Variables and functions */
 size_t ADV748X_HDMI_SOURCE ; 
 int ENOLINK ; 
 int adv748x_csi2_set_pixelrate (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 struct v4l2_subdev* adv748x_get_remote_sd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adv748x_hdmi_query_dv_timings (int /*<<< orphan*/ *,struct v4l2_dv_timings*) ; 

__attribute__((used)) static int adv748x_hdmi_propagate_pixelrate(struct adv748x_hdmi *hdmi)
{
	struct v4l2_subdev *tx;
	struct v4l2_dv_timings timings;

	tx = adv748x_get_remote_sd(&hdmi->pads[ADV748X_HDMI_SOURCE]);
	if (!tx)
		return -ENOLINK;

	adv748x_hdmi_query_dv_timings(&hdmi->sd, &timings);

	return adv748x_csi2_set_pixelrate(tx, timings.bt.pixelclock);
}