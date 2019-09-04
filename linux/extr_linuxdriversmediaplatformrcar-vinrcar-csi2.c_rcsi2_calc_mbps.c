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
typedef  int u64 ;
struct v4l2_subdev {int /*<<< orphan*/  name; int /*<<< orphan*/  ctrl_handler; } ;
struct v4l2_ctrl {int dummy; } ;
struct rcar_csi2 {int lanes; int /*<<< orphan*/  dev; struct v4l2_subdev* remote; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  V4L2_CID_PIXEL_RATE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 struct v4l2_ctrl* v4l2_ctrl_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int v4l2_ctrl_g_ctrl_int64 (struct v4l2_ctrl*) ; 

__attribute__((used)) static int rcsi2_calc_mbps(struct rcar_csi2 *priv, unsigned int bpp)
{
	struct v4l2_subdev *source;
	struct v4l2_ctrl *ctrl;
	u64 mbps;

	if (!priv->remote)
		return -ENODEV;

	source = priv->remote;

	/* Read the pixel rate control from remote. */
	ctrl = v4l2_ctrl_find(source->ctrl_handler, V4L2_CID_PIXEL_RATE);
	if (!ctrl) {
		dev_err(priv->dev, "no pixel rate control in subdev %s\n",
			source->name);
		return -EINVAL;
	}

	/*
	 * Calculate the phypll in mbps.
	 * link_freq = (pixel_rate * bits_per_sample) / (2 * nr_of_lanes)
	 * bps = link_freq * 2
	 */
	mbps = v4l2_ctrl_g_ctrl_int64(ctrl) * bpp;
	do_div(mbps, priv->lanes * 1000000);

	return mbps;
}