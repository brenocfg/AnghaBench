#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct v4l2_subdev {int /*<<< orphan*/  ctrl_handler; } ;
struct TYPE_6__ {int num_data_lanes; } ;
struct TYPE_5__ {TYPE_3__ mipi_csi2; } ;
struct v4l2_fwnode_endpoint {TYPE_2__ bus; } ;
struct v4l2_ctrl {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  code; } ;
struct mipid02_dev {TYPE_1__ fmt; struct v4l2_fwnode_endpoint rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_CID_PIXEL_RATE ; 
 int bpp_from_code (int /*<<< orphan*/ ) ; 
 struct v4l2_ctrl* v4l2_ctrl_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int v4l2_ctrl_g_ctrl_int64 (struct v4l2_ctrl*) ; 

__attribute__((used)) static u32 mipid02_get_link_freq_from_cid_pixel_rate(struct mipid02_dev *bridge,
						     struct v4l2_subdev *subdev)
{
	struct v4l2_fwnode_endpoint *ep = &bridge->rx;
	struct v4l2_ctrl *ctrl;
	u32 pixel_clock;
	u32 bpp = bpp_from_code(bridge->fmt.code);

	ctrl = v4l2_ctrl_find(subdev->ctrl_handler, V4L2_CID_PIXEL_RATE);
	if (!ctrl)
		return 0;
	pixel_clock = v4l2_ctrl_g_ctrl_int64(ctrl);

	return pixel_clock * bpp / (2 * ep->bus.mipi_csi2.num_data_lanes);
}