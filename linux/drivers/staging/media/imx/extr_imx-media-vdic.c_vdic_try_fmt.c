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
typedef  int /*<<< orphan*/  u32 ;
struct vdic_priv {int /*<<< orphan*/  active_input_pad; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  code; } ;
struct v4l2_subdev_format {int pad; struct v4l2_mbus_framefmt format; int /*<<< orphan*/  which; } ;
struct imx_media_pixfmt {int /*<<< orphan*/ * codes; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_SEL_YUV ; 
 int /*<<< orphan*/  H_ALIGN ; 
 int /*<<< orphan*/  MAX_H_VDIC ; 
 int /*<<< orphan*/  MAX_W_VDIC ; 
 int /*<<< orphan*/  MIN_H ; 
 int /*<<< orphan*/  MIN_W ; 
 int /*<<< orphan*/  S_ALIGN ; 
 int /*<<< orphan*/  V4L2_FIELD_HAS_BOTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_FIELD_SEQ_TB ; 
#define  VDIC_SINK_PAD_DIRECT 130 
#define  VDIC_SINK_PAD_IDMAC 129 
#define  VDIC_SRC_PAD_DIRECT 128 
 int /*<<< orphan*/  W_ALIGN ; 
 struct v4l2_mbus_framefmt* __vdic_get_fmt (struct vdic_priv*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_media_enum_ipu_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct imx_media_pixfmt* imx_media_find_ipu_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_media_try_colorimetry (struct v4l2_mbus_framefmt*,int) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vdic_try_fmt(struct vdic_priv *priv,
			 struct v4l2_subdev_pad_config *cfg,
			 struct v4l2_subdev_format *sdformat,
			 const struct imx_media_pixfmt **cc)
{
	struct v4l2_mbus_framefmt *infmt;

	*cc = imx_media_find_ipu_format(sdformat->format.code, CS_SEL_YUV);
	if (!*cc) {
		u32 code;

		imx_media_enum_ipu_format(&code, 0, CS_SEL_YUV);
		*cc = imx_media_find_ipu_format(code, CS_SEL_YUV);
		sdformat->format.code = (*cc)->codes[0];
	}

	infmt = __vdic_get_fmt(priv, cfg, priv->active_input_pad,
			       sdformat->which);

	switch (sdformat->pad) {
	case VDIC_SRC_PAD_DIRECT:
		sdformat->format = *infmt;
		/* output is always progressive! */
		sdformat->format.field = V4L2_FIELD_NONE;
		break;
	case VDIC_SINK_PAD_DIRECT:
	case VDIC_SINK_PAD_IDMAC:
		v4l_bound_align_image(&sdformat->format.width,
				      MIN_W, MAX_W_VDIC, W_ALIGN,
				      &sdformat->format.height,
				      MIN_H, MAX_H_VDIC, H_ALIGN, S_ALIGN);

		/* input must be interlaced! Choose SEQ_TB if not */
		if (!V4L2_FIELD_HAS_BOTH(sdformat->format.field))
			sdformat->format.field = V4L2_FIELD_SEQ_TB;
		break;
	}

	imx_media_try_colorimetry(&sdformat->format, true);
}