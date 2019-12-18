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
typedef  int u32 ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_rect {int width; scalar_t__ left; int height; int top; } ;
struct v4l2_mbus_framefmt {int width; int height; scalar_t__ field; } ;
struct v4l2_fwnode_endpoint {scalar_t__ bus_type; } ;
struct csi_priv {scalar_t__ active_output_pad; } ;

/* Variables and functions */
 scalar_t__ CSI_SRC_PAD_DIRECT ; 
 scalar_t__ V4L2_FIELD_ALTERNATE ; 
 scalar_t__ V4L2_FIELD_HAS_BOTH (scalar_t__) ; 
 scalar_t__ V4L2_MBUS_BT656 ; 
 int /*<<< orphan*/  __u32 ; 
 void* min_t (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void csi_try_crop(struct csi_priv *priv,
			 struct v4l2_rect *crop,
			 struct v4l2_subdev_pad_config *cfg,
			 struct v4l2_mbus_framefmt *infmt,
			 struct v4l2_fwnode_endpoint *upstream_ep)
{
	u32 in_height;

	crop->width = min_t(__u32, infmt->width, crop->width);
	if (crop->left + crop->width > infmt->width)
		crop->left = infmt->width - crop->width;
	/* adjust crop left/width to h/w alignment restrictions */
	crop->left &= ~0x3;
	if (priv->active_output_pad == CSI_SRC_PAD_DIRECT)
		crop->width &= ~0x7; /* multiple of 8 pixels (IC burst) */
	else
		crop->width &= ~0x1; /* multiple of 2 pixels */

	in_height = infmt->height;
	if (infmt->field == V4L2_FIELD_ALTERNATE)
		in_height *= 2;

	/*
	 * FIXME: not sure why yet, but on interlaced bt.656,
	 * changing the vertical cropping causes loss of vertical
	 * sync, so fix it to NTSC/PAL active lines. NTSC contains
	 * 2 extra lines of active video that need to be cropped.
	 */
	if (upstream_ep->bus_type == V4L2_MBUS_BT656 &&
	    (V4L2_FIELD_HAS_BOTH(infmt->field) ||
	     infmt->field == V4L2_FIELD_ALTERNATE)) {
		crop->height = in_height;
		crop->top = (in_height == 480) ? 2 : 0;
	} else {
		crop->height = min_t(__u32, in_height, crop->height);
		if (crop->top + crop->height > in_height)
			crop->top = in_height - crop->height;
	}
}