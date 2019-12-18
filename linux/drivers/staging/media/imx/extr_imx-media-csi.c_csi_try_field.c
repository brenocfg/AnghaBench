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
struct v4l2_subdev_pad_config {int dummy; } ;
struct TYPE_2__ {scalar_t__ field; } ;
struct v4l2_subdev_format {scalar_t__ pad; TYPE_1__ format; int /*<<< orphan*/  which; } ;
struct v4l2_mbus_framefmt {int field; int height; } ;
struct csi_priv {int dummy; } ;

/* Variables and functions */
 scalar_t__ CSI_SINK_PAD ; 
#define  V4L2_FIELD_ALTERNATE 130 
 scalar_t__ V4L2_FIELD_ANY ; 
 int /*<<< orphan*/  V4L2_FIELD_IS_SEQUENTIAL (scalar_t__) ; 
 scalar_t__ V4L2_FIELD_NONE ; 
#define  V4L2_FIELD_SEQ_BT 129 
#define  V4L2_FIELD_SEQ_TB 128 
 struct v4l2_mbus_framefmt* __csi_get_fmt (struct csi_priv*,struct v4l2_subdev_pad_config*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void csi_try_field(struct csi_priv *priv,
			  struct v4l2_subdev_pad_config *cfg,
			  struct v4l2_subdev_format *sdformat)
{
	struct v4l2_mbus_framefmt *infmt =
		__csi_get_fmt(priv, cfg, CSI_SINK_PAD, sdformat->which);

	/*
	 * no restrictions on sink pad field type except must
	 * be initialized.
	 */
	if (sdformat->pad == CSI_SINK_PAD) {
		if (sdformat->format.field == V4L2_FIELD_ANY)
			sdformat->format.field = V4L2_FIELD_NONE;
		return;
	}

	switch (infmt->field) {
	case V4L2_FIELD_SEQ_TB:
	case V4L2_FIELD_SEQ_BT:
		/*
		 * If the user requests sequential at the source pad,
		 * allow it (along with possibly inverting field order).
		 * Otherwise passthrough the field type.
		 */
		if (!V4L2_FIELD_IS_SEQUENTIAL(sdformat->format.field))
			sdformat->format.field = infmt->field;
		break;
	case V4L2_FIELD_ALTERNATE:
		/*
		 * This driver does not support alternate field mode, and
		 * the CSI captures a whole frame, so the CSI never presents
		 * alternate mode at its source pads. If user has not
		 * already requested sequential, translate ALTERNATE at
		 * sink pad to SEQ_TB or SEQ_BT at the source pad depending
		 * on input height (assume NTSC BT order if 480 total active
		 * frame lines, otherwise PAL TB order).
		 */
		if (!V4L2_FIELD_IS_SEQUENTIAL(sdformat->format.field))
			sdformat->format.field = (infmt->height == 480 / 2) ?
				V4L2_FIELD_SEQ_BT : V4L2_FIELD_SEQ_TB;
		break;
	default:
		/* Passthrough for all other input field types */
		sdformat->format.field = infmt->field;
		break;
	}
}